# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 18:19:23 by jsurian           #+#    #+#              #
#    Updated: 2025/09/24 16:23:07 by jsurian42        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

.PHONY: clean fclean all re

SRCS = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strremove_str.c\
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_strdupdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_split_free.c\
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c 

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstsplit.c

OBJS = $(SRCS:.c=.o) ${BONUS:.c=.o}

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

# Détection de l'OS pour compatibilité macOS/Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	# macOS - l'option -U n'existe pas
	ARFLAGS = -ru -s -v
else
	# Linux - comportement original
	ARFLAGS = -ru -s -U -v
endif

NAME = libft.a

.INTERMEDIATE: $(OBJS)

all:$(NAME)

$(NAME): $(NAME)($(OBJS))

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test-ft_lstsplit: libft.a
test-ft_strdupdup: libft.a
