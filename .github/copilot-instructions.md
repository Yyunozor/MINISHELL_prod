# Copilot Instructions (Minishell)
Concise guide for contributing AI changes safely & test-compliantly (target: Bash‑like behavior, strict error/exit codes, no leaks).

Core dirs: parsing/, executing/, expansion/, redirections/, builtins/, libft/, includes/.
Flow: line → parse tokens/simple commands → expand → redirections → builtin or path resolve → (fork+exec) or direct builtin → collect status.

Exit codes: 127 command not found; 126 is directory/permission; 2 syntax; 1 generic builtin/runtime; cd errors mirror Bash wording (`minishell: cd:`); missing $VAR → empty.

Error format: always prefix `minishell:` (add builtin name if relevant). Directory exec blocked early (stat + S_ISDIR) before execve.

Expansion: exact env name match only; duplicate strings (never reuse env array memory) to avoid double free.

PATH: search only when cmd has no '/'; else use literal path. On failure after search: print `minishell: <cmd>: command not found` (127).

Builtins: echo supports multiple -n flags; export/unset validate identifiers (invalid → stderr, exit 1, no mutation); cd updates PWD/OLDPWD only on success; exit non-numeric → message + 255.

Memory & FDs: free per simple command; close any opened redir FDs on failure; free PATH split arrays (ft_split_free).

Parsing errors: set last_exit_status=2 immediately so `$?` reflects it; do not attempt execution of that line.

Linked list safety: mixed node list must be distinguished (is_scmd flag) before freeing.

Adding feature/builtin: add prototype (includes/), implement in builtins/ (or subsystem), register in dispatcher, preserve error prefixes & exit codes, reuse libft.

Common pitfalls: env partial matches, directory mistaken for not found (126 vs 127), forgetting to duplicate expansion strings, losing syntax error code propagation.

Quick checklist before committing:
1. Messages prefixed correctly?
2. Exit codes match Bash cases?
3. No leaked splits / heredoc temps?
4. Added headers & prototypes synced?
5. New logic covered by simple manual test (cmd; echo $?)?

Keep patches focused; avoid speculative refactors.
