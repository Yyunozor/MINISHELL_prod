#!/usr/bin/env bash

# Automated evaluation script inspired by the official 42 minishell peer-evaluation sheet.
# It builds, tests, and scores the project, producing logs inside .eval_logs/.

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR"
MINISHELL_BIN="$PROJECT_ROOT/minishell"
TESTER_DIR="$PROJECT_ROOT/minishell_tester"
LOG_ROOT="$PROJECT_ROOT/.eval_logs"
mkdir -p "$LOG_ROOT"

TMP_ROOT="$(mktemp -d "${TMPDIR:-/tmp}/minishell-eval-XXXX")"
cleanup() {
    rm -rf "$TMP_ROOT"
}
trap cleanup EXIT INT TERM

USE_COLOR=1
RUN_HEAVY=1
while [[ $# -gt 0 ]]; do
    case "$1" in
        --no-color) USE_COLOR=0 ;;
        --light) RUN_HEAVY=0 ;;
        *) echo "Unknown option: $1" >&2; exit 1 ;;
    esac
    shift
done

if [[ $USE_COLOR -eq 1 ]]; then
    BOLD="\e[1m"; DIM="\e[2m"; GREEN="\e[32m"; YELLOW="\e[33m"; RED="\e[31m"; BLUE="\e[34m"; MAGENTA="\e[35m"; RESET="\e[0m"
else
    BOLD=""; DIM=""; GREEN=""; YELLOW=""; RED=""; BLUE=""; MAGENTA=""; RESET=""
fi

print_section() {
    printf "\n${BOLD}%s${RESET}\n" "$1"
    printf '%*s\n' "${#1}" '' | tr ' ' '-'
}

info() { printf "%s\n" "$1"; }
ok() { printf "  ${GREEN}✔${RESET} %s\n" "$1"; }
warn() { printf "  ${YELLOW}!${RESET} %s\n" "$1"; }
ko() { printf "  ${RED}✘${RESET} %s\n" "$1"; }

TOTAL_MAX=0
TOTAL_SCORE=0
FAILED_SUMMARY=()

BONUS_MAX=0
BONUS_SCORE=0
BONUS_SUMMARY=()

PENDING_SUMMARY=()

record_success() {
    local label=$1 points=$2 bonus=${3:-0}
    if (( bonus )); then
        BONUS_MAX=$((BONUS_MAX + points))
        BONUS_SCORE=$((BONUS_SCORE + points))
        ok "$label (${points} pts bonus)"
    else
        TOTAL_MAX=$((TOTAL_MAX + points))
        TOTAL_SCORE=$((TOTAL_SCORE + points))
        ok "$label (${points} pts)"
    fi
}

record_failure() {
    local label=$1 points=$2 bonus=${3:-0}
    if (( bonus )); then
        BONUS_MAX=$((BONUS_MAX + points))
        BONUS_SUMMARY+=("$label (${points} pts bonus)")
        ko "$label (${points} pts bonus)"
    else
        TOTAL_MAX=$((TOTAL_MAX + points))
        FAILED_SUMMARY+=("$label (${points} pts)")
        ko "$label (${points} pts)"
    fi
}

record_pending() {
    local label=$1 points=$2 bonus=${3:-0}
    if (( bonus )); then
        BONUS_MAX=$((BONUS_MAX + points))
        BONUS_SUMMARY+=("Pending manual: $label (${points} pts bonus)")
        warn "$label (${points} pts bonus — manual)"
    else
        TOTAL_MAX=$((TOTAL_MAX + points))
        PENDING_SUMMARY+=("Pending manual: $label (${points} pts)")
        warn "$label (${points} pts — manual)"
    fi
}

ENV_PREFIX=(
    env -i
    PATH="$PATH"
    HOME="${HOME:-$PROJECT_ROOT}"
    USER="${USER:-minishell}"
    TERM="${TERM:-xterm-256color}"
    PWD="$PROJECT_ROOT"
    OLDPWD="$PROJECT_ROOT"
    SHLVL=1
    PS1=
    LC_ALL=C
    LSCOLORS=
)

require_binary() {
    if [[ ! -x "$MINISHELL_BIN" ]]; then
        ko "Missing minishell binary at $MINISHELL_BIN"
        exit 1
    fi
}

slugify() {
    echo "$1" | tr '[:upper:]' '[:lower:]' | tr -cs '[:alnum:]' '_' | sed 's/^_\+//;s/_\+$//'
}

run_norminette() {
    local points=10
    local log="$LOG_ROOT/norminette.log"
    print_section "Norminette"
    if ! command -v norminette >/dev/null 2>&1; then
        record_pending "norminette binary not found" "$points"
        info "Install norminette or run the check manually."
        return
    fi
    info "Running norminette on includes/ and src/"
    if norminette includes src >"$log" 2>&1; then
        record_success "Norminette clean" "$points"
    else
        record_failure "Norminette errors (see $log)" "$points"
    fi
}

run_make_target() {
    local target=$1 points=$2 label=$3
    local log="$LOG_ROOT/make_${target:-all}.log"
    if [[ -z $target ]]; then
        if make -C "$PROJECT_ROOT" >"$log" 2>&1; then
            record_success "$label" "$points"
        else
            record_failure "$label (see $log)" "$points"
        fi
        return
    fi
    if make -C "$PROJECT_ROOT" "$target" >"$log" 2>&1; then
        record_success "$label" "$points"
    else
        record_failure "$label (see $log)" "$points"
    fi
}

run_leak_check() {
    local points=6
    local log="$LOG_ROOT/leaks.log"
    print_section "Leak check"
    printf 'echo leak-test\nexit\n' >"$TMP_ROOT/leak.in"
    if command -v valgrind >/dev/null 2>&1; then
        info "Using valgrind --leak-check=full"
        if "${ENV_PREFIX[@]}" valgrind --leak-check=full --quiet --error-exitcode=1 "$MINISHELL_BIN" <"$TMP_ROOT/leak.in" >"$TMP_ROOT/leak.out" 2>"$log"; then
            record_success "No leaks detected by valgrind" "$points"
        else
            record_failure "Leaks detected (see $log)" "$points"
        fi
    elif command -v leaks >/dev/null 2>&1; then
        info "Using leaks --atExit"
        if "${ENV_PREFIX[@]}" leaks --atExit -- "$MINISHELL_BIN" <"$TMP_ROOT/leak.in" >"$TMP_ROOT/leak.out" 2>"$log"; then
            record_success "No leaks detected by leaks" "$points"
        else
            if grep -qi "not debuggable" "$log"; then
                record_pending "leaks could not attach (see $log)" "$points"
            else
                record_failure "Leaks detected (see $log)" "$points"
            fi
        fi
    else
        record_pending "Run leak checker (valgrind or leaks)" "$points"
    fi
}

declare -a TEST_MODE TEST_NAME TEST_POINTS TEST_COMMANDS TEST_EXTRA TEST_IS_BONUS

add_compare() {
    local name=$1 points=$2 commands=$3 bonus=${4:-0}
    TEST_MODE+=("compare")
    TEST_NAME+=("$name")
    TEST_POINTS+=("$points")
    TEST_COMMANDS+=("$commands")
    TEST_EXTRA+=("")
    TEST_IS_BONUS+=("$bonus")
}

add_contains() {
    local name=$1 points=$2 commands=$3 expected=$4 bonus=${5:-0}
    TEST_MODE+=("contains")
    TEST_NAME+=("$name")
    TEST_POINTS+=("$points")
    TEST_COMMANDS+=("$commands")
    TEST_EXTRA+=("$expected")
    TEST_IS_BONUS+=("$bonus")
}

run_compare_test() {
    local idx=$1
    local name=${TEST_NAME[$idx]}
    local points=${TEST_POINTS[$idx]}
    local commands=${TEST_COMMANDS[$idx]}
    local bonus=${TEST_IS_BONUS[$idx]}

    local case_tmp
    case_tmp="$(mktemp -d "$TMP_ROOT/case-${idx}-XXXX")"
    local input_file="$case_tmp/input.sh"
    printf "%s\nexit\n" "$commands" >"$input_file"

    local mini_stdout="$case_tmp/mini.out"
    local mini_stderr="$case_tmp/mini.err"
    local bash_stdout="$case_tmp/bash.out"
    local bash_stderr="$case_tmp/bash.err"

    (cd "$PROJECT_ROOT" && "${ENV_PREFIX[@]}" EVAL_TMP="$case_tmp" "$MINISHELL_BIN" <"$input_file" >"$mini_stdout" 2>"$mini_stderr")
    local mini_status=$?
    (cd "$PROJECT_ROOT" && "${ENV_PREFIX[@]}" EVAL_TMP="$case_tmp" bash --noprofile --norc <"$input_file" >"$bash_stdout" 2>"$bash_stderr")
    local bash_status=$?

    local diff_output
    if diff_output=$(diff -u <(cat "$bash_stdout" "$bash_stderr") <(cat "$mini_stdout" "$mini_stderr")); then
        if [[ $mini_status -eq $bash_status ]]; then
            record_success "$name" "$points" "$bonus"
        else
            local slug="$(slugify "$name")"
            local log="$LOG_ROOT/${idx}_${slug}.diff"
            {
                echo "Mini exit: $mini_status"
                echo "Bash exit: $bash_status"
                echo "--- diff"
                printf "%s\n" "$diff_output"
            } >"$log"
            record_failure "$name (exit mismatch, see $log)" "$points" "$bonus"
        fi
    else
        local slug="$(slugify "$name")"
        local log="$LOG_ROOT/${idx}_${slug}.diff"
        {
            echo "Mini exit: $mini_status"
            echo "Bash exit: $bash_status"
            echo "--- diff"
            printf "%s\n" "$diff_output"
            echo "--- minishell stdout"
            cat "$mini_stdout"
            echo "--- minishell stderr"
            cat "$mini_stderr"
            echo "--- bash stdout"
            cat "$bash_stdout"
            echo "--- bash stderr"
            cat "$bash_stderr"
        } >"$log"
        record_failure "$name (output diff, see $log)" "$points" "$bonus"
    fi
}

run_contains_test() {
    local idx=$1
    local name=${TEST_NAME[$idx]}
    local points=${TEST_POINTS[$idx]}
    local commands=${TEST_COMMANDS[$idx]}
    local expected=${TEST_EXTRA[$idx]}
    local bonus=${TEST_IS_BONUS[$idx]}

    local case_tmp
    case_tmp="$(mktemp -d "$TMP_ROOT/case-${idx}-XXXX")"
    local input_file="$case_tmp/input.sh"
    printf "%s\nexit\n" "$commands" >"$input_file"

    local mini_stdout="$case_tmp/mini.out"
    local mini_stderr="$case_tmp/mini.err"
    (cd "$PROJECT_ROOT" && "${ENV_PREFIX[@]}" EVAL_TMP="$case_tmp" "$MINISHELL_BIN" <"$input_file" >"$mini_stdout" 2>"$mini_stderr")
    if grep -q "$expected" "$mini_stdout" "$mini_stderr"; then
        record_success "$name" "$points" "$bonus"
    else
        local slug="$(slugify "$name")"
        local log="$LOG_ROOT/${idx}_${slug}.log"
        {
            echo "Expected: $expected"
            echo "--- minishell stdout"
            cat "$mini_stdout"
            echo "--- minishell stderr"
            cat "$mini_stderr"
        } >"$log"
        record_failure "$name (missing pattern, see $log)" "$points" "$bonus"
    fi
}

print_section "Build checks"
run_make_target fclean 2 "make fclean"
run_make_target "" 4 "make"
run_make_target clean 2 "make clean"
run_make_target re 2 "make re"
require_binary

run_norminette
run_leak_check

print_section "Mandatory functional tests"
add_compare "Builtin echo & echo -n" 6 "$(printf '%s\n' 'echo "hello world"' 'echo -n "no newline"')"
add_compare "Builtin cd / pwd" 6 "$(printf '%s\n' 'pwd' 'cd ..' 'pwd' "cd \"$PROJECT_ROOT\"" 'pwd')"
add_compare "Builtin export/unset/env" 6 "$(printf '%s\n' 'export NEWVAR=abc' 'echo $NEWVAR' 'unset NEWVAR' 'echo [$NEWVAR]' 'env | grep NEWVAR')"
add_compare "Builtin exit & status" 5 "$(printf '%s\n' 'false' 'echo $?' 'true' 'echo $?' 'exit 42')"
add_compare "External commands" 5 "$(printf '%s\n' 'ls' 'cat test_input.txt')"
add_compare "Pipes simple" 5 "$(printf '%s\n' 'printf "a\n" | cat -e')"
add_compare "Pipes multiple" 5 "$(printf '%s\n' 'printf "1\n2\n" | grep 1 | tr "1" "9"')"
add_compare "Redirections > and >>" 6 "$(printf '%s\n' 'rm -f "$EVAL_TMP/out"' 'echo first > "$EVAL_TMP/out"' 'echo second >> "$EVAL_TMP/out"' 'cat "$EVAL_TMP/out"')"
add_compare "Redirection <" 4 "$(printf '%s\n' 'cat <<EOF > "$EVAL_TMP/in.txt"' 'infile content' 'EOF' 'cat < "$EVAL_TMP/in.txt"')"
add_compare "Heredoc" 6 "$(printf '%s\n' 'cat <<EOF' 'heredoc line' 'EOF')"
add_compare "Quote handling" 2 "$(printf '%s\n' 'echo "\"mini\" shell"' "echo 'single quote'")"
add_compare "Variable expansion & $?" 6 "$(printf '%s\n' 'export VAR=mini' 'echo ${VAR}_shell' 'false' 'echo $?')"

MANDATORY_COUNT=${#TEST_MODE[@]}
for ((i = 0; i < MANDATORY_COUNT; ++i)); do
    case ${TEST_MODE[$i]} in
        compare) run_compare_test "$i" ;;
        contains) run_contains_test "$i" ;;
    esac
done

print_section "Bonus functional tests"
add_compare "Wildcard expansion" 5 "$(printf '%s\n' 'rm -rf "$EVAL_TMP/wild"' 'mkdir -p "$EVAL_TMP/wild"' 'touch "$EVAL_TMP/wild/a.c" "$EVAL_TMP/wild/b.txt" "$EVAL_TMP/wild/readme"' 'cd "$EVAL_TMP/wild" && printf "%s\n" *')" 1

for ((i = MANDATORY_COUNT; i < ${#TEST_MODE[@]}; ++i)); do
    case ${TEST_MODE[$i]} in
        compare) run_compare_test "$i" ;;
        contains) run_contains_test "$i" ;;
    esac
done

print_section "Manual checklist"
record_pending "Prompt displays correctly on interactive TTY" 2
record_pending "History navigation (Up/Down)" 2
record_pending "Ctrl-C prints new prompt and resets line" 2
record_pending "Ctrl-D exits with code 0" 2
record_pending "Ctrl-\\ ignored in interactive mode" 2
record_pending "Global variable policy (code review)" 2

if [[ $RUN_HEAVY -eq 1 && -x "$TESTER_DIR/tester" ]]; then
    print_section "Extended minishell_tester"
    tester_log="$LOG_ROOT/minishell_tester.log"
    if (cd "$TESTER_DIR" && ./tester >"$tester_log" 2>&1); then
        record_success "minishell_tester (builtins/pipes/redirects/extras)" 10 1
    else
        record_failure "minishell_tester suite (see $tester_log)" 10 1
    fi
else
    warn "Skipping minishell_tester extended run"
fi

print_section "Score"
info "Mandatory: ${TOTAL_SCORE} / ${TOTAL_MAX}"
if (( BONUS_MAX > 0 )); then
    info "Bonus: ${BONUS_SCORE} / ${BONUS_MAX}"
fi

if [[ ${#FAILED_SUMMARY[@]} -gt 0 ]]; then
    printf "\n${RED}Issues:${RESET}\n"
    for item in "${FAILED_SUMMARY[@]}"; do
        printf "  - %s\n" "$item"
    done
fi

if [[ ${#PENDING_SUMMARY[@]} -gt 0 ]]; then
    printf "\n${YELLOW}Manual checks:${RESET}\n"
    for item in "${PENDING_SUMMARY[@]}"; do
        printf "  - %s\n" "$item"
    done
fi

if [[ ${#BONUS_SUMMARY[@]} -gt 0 ]]; then
    printf "\n${MAGENTA}Bonus pending:${RESET}\n"
    for item in "${BONUS_SUMMARY[@]}"; do
        printf "  - %s\n" "$item"
    done
fi

info "Logs stored in $LOG_ROOT"
