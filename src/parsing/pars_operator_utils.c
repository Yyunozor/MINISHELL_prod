/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_operator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:00:00 by GitHub Copilot   #+#    #+#             */
/*   Updated: 2024/10/30 00:00:00 by GitHub Copilot  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_token_struct_op(char *str, t_utils_op *u, t_token **token,
		int size)
{
	(*token)->str = malloc(sizeof(char) * (size + 1));
	if (!(*token)->str)
		return (1);
	ft_memcpy((*token)->str, str + u->i_start, size);
	(*token)->str[size] = '\0';
	(*token)->type = u->state_node;
	return (0);
}

static int	add_node_op(char *str, t_utils_op *u, int size)
{
	t_token	*token;
	t_list	*new_node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (1);
	if (set_token_struct_op(str, u, &token, size))
	{
		free(token);
		return (1);
	}
	new_node = ft_lstnew(token);
	if (!new_node)
	{
		free(token);
		return (1);
	}
	if (!u->list_head)
		u->list_head = new_node;
	else
		ft_lstadd_back(&u->list_head, new_node);
	return (0);
}

static int	lst_split_store_match(char *str, t_utils_op *u,
		const char *pattern, int index)
{
	size_t	len;

	len = ft_strlen(pattern);
	u->state_node = index;
	if (add_node_op(str, u, len))
		return (1);
	u->i_start += len;
	u->i_continue = 1;
	return (0);
}

static int	lst_split_try_patterns(char *str, t_utils_op *u)
{
	static const char *const	patterns[] = {
		">>",
		"<<",
		">",
		"<",
		"|",
		" ",
		NULL
	};
	size_t	len;

	u->y = 0;
	while (patterns[u->y])
	{
		len = ft_strlen(patterns[u->y]);
		if (!ft_strncmp(str + u->i_start, patterns[u->y], len))
			return (lst_split_store_match(str, u, patterns[u->y], u->y));
		u->y++;
	}
	return (0);
}

t_list	*lst_str_split(char *str)
{
	t_utils_op	u;

	u.i_start = 0;
	u.i_continue = 0;
	u.list_head = NULL;
	u.y = 0;
	u.state_node = 0;
	while (str[u.i_start])
	{
		u.i_continue = 0;
		if (lst_split_try_patterns(str, &u))
		{
			if (!u.i_continue)
				return (NULL);
			continue ;
		}
		if (!u.i_continue)
			u.i_start += 1;
	}
	return (u.list_head);
}
