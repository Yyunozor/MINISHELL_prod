/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_scmd_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:33:49 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 04:58:02 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	scmd_count_argv(t_list *token_list)
{
	size_t	i;
	t_list	*prev_lst;

	i = 0;
	prev_lst = NULL;
	while (token_list)
	{
		if (token_list->token->type > PIPE && (!prev_lst
				|| prev_lst->token->type > PIPE))
			i++;
		prev_lst = token_list;
		token_list = token_list->next;
	}
	return (i);
}

int	scmd_parse_argv(t_scmd *self, t_list *token_list)
{
	size_t	size_argv;
	size_t	i;
	t_list	*prev_lst;

	prev_lst = NULL;
	size_argv = scmd_count_argv(token_list);
	self->argv = malloc(sizeof(char *) * (size_argv + 1));
	if (!self->argv)
		return (1);
	i = 0;
	while (token_list)
	{
		if (token_list->token->type > PIPE && (!prev_lst
				|| prev_lst->token->type > PIPE))
		{
			self->argv[i] = token_list->token->str;
			i++;
		}
		prev_lst = token_list;
		token_list = token_list->next;
	}
	self->argv[i] = NULL;
	self->nbr_of_argv = size_argv;
	return (0);
}

void	scmd_parse_command_path(t_scmd *self)
{
	self->command_path = NULL;
}

void	scmd_parse_env(t_scmd *self, char **envp)
{
	self->env = envp;
}
