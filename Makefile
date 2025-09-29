# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 14:54:47 by jsurian42         #+#    #+#              #
#    Updated: 2025/09/29 17:19:35 by anpayot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

vpath		%.c src/parsing:src/executing:src:src/expansion:src/builtins:src/redirections:src/signals

PARSING_SOURCES := \
		   parsing.c\
		   pars_init.c\
		   pars_metacar.c\
		   pars_operator.c\
		   pars_operator_utils.c\
		   pars_space.c\
		   pars_pipe_split.c\
		   pars_scmd.c\
		   pars_scmd_argv.c\
		   pars_scmd_red.c\
		   pars_utils.c\
		   parsing_utils.c

EXECUTING_SOURCES := \
		   executing.c\
		   exec_init.c\
		   exec_pipeline.c\
		   exec_simple_builtin.c\
		   exec_child.c\
		   exec_expansion.c\
		   exec_expansion_utils.c\
		   exec_child_set_path.c\
		   exec_parent.c

EXPAND_SOURCES := \
			expand_str.c\
			expand_quotes.c\
			expand_get_env_value.c

REDIRECTIONS_SOURCES := \
			exec_redirections.c \
			exec_heredoc.c\
			heredoc_utils.c\
			heredoc_cleanup.c

BUILTINS_SOURCES := \
			builtin_core.c\
			ft_cd.c\
			cd_utils.c\
			ft_env.c\
			env_management.c\
			env_remove.c\
			ft_export.c\
			export_helpers.c\
			ft_echo.c\
			ft_unset.c\
			ft_exit.c\
			ft_pwd.c

SIGNALS_SOURCES := \
		   signals_prompt.c\
		   signals_exec.c\
		   signals_heredoc.c\
		   signals_state.c

SOURCES := minishell.c $(PARSING_SOURCES) $(EXECUTING_SOURCES) $(EXPAND_SOURCES) $(REDIRECTIONS_SOURCES) $(BUILTINS_SOURCES) $(SIGNALS_SOURCES)

libft/libft.a:
	$(MAKE) -C libft

##################################

.DEFAULT_GOAL	:= all

CC			:= gcc
CFLAGS 		:= -g -Wall -Werror -Wextra

# Détection de l'OS pour compatibilité macOS/Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	# macOS - chemins Homebrew pour readline
	CPPFLAGS	:= -Iincludes -Iincludes/parsing -Iincludes/executing -Iincludes/expansion -Iincludes/redirections -Iincludes/builtins -Ilibft -I/opt/homebrew/include
	LDFLAGS		:= -L/opt/homebrew/lib -lreadline
else
	# Linux - comportement original
	CPPFLAGS	:= -Iincludes -Iincludes/parsing -Iincludes/executing -Iincludes/expansion -Iincludes/redirections -Iincludes/builtins -Ilibft
	LDFLAGS		:= -lreadline
endif

OBJETS := $(SOURCES:%.c=%.o)

.INTERMEDIATE:	$(OBJETS)

$(NAME) : $(OBJETS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJETS) libft/libft.a $(LDFLAGS) -o $(NAME)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) *.o

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

.PHONY: re
re: fclean all
