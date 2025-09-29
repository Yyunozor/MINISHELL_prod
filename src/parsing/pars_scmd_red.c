/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_scmd_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:23:33 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/25 23:11:09 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	red_syntax_error(char *token, t_scmd *self)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	// Cleanup minimal - le cleanup complet se fait dans scmd_create
	(void)self;
	return (1);
}

// Creates one redir from a redir token node
int	red_from_red_node(t_red *self, t_list *red_node, t_scmd *scmd)
{
	self->type = red_node->token->type;
	if (!red_node->next)
	{
		return (red_syntax_error(NULL, scmd));
	}
	else if (red_node->next->token->type <= PIPE)
	{
		return (red_syntax_error(red_node->next->token->str, scmd));
	}
	self->word = red_node->next->token->str;
	if (red_node->token->type == RED_HEREDOC
		&& (ft_strchr(self->word, '\'')
			|| ft_strchr(self->word, '"')))
		self->quoted_heredoc = 1;
	else
		self->quoted_heredoc = 0;
	return (0);
}

int	token_is_red(t_token *self)
{
	if (self->type < PIPE)
		return (1);
	else
		return (0);
}

void	scmd_count_red(t_scmd *self, t_list *token_list)
{
	size_t	nb_red;

	nb_red = 0;
	while (token_list)
	{
		if (token_is_red(token_list->token))
			nb_red++;
		token_list = token_list->next;
	}
	self->nbr_of_red = nb_red;
}

// Create an array of redir
int	scmd_parse_red(t_scmd *self, t_list *token_list)
{
	t_red	*new_red_tab;
	size_t	i;

	scmd_count_red(self, token_list);
	new_red_tab = ft_calloc(self->nbr_of_red, sizeof(t_red));
	if (!new_red_tab)
		return (1);
	i = 0;
	while (token_list)
	{
		if (token_is_red(token_list->token))
		{
			if (red_from_red_node(&new_red_tab[i], token_list, self))
			{
				free(new_red_tab);
				return (1);
			}
			i++;
		}
		token_list = token_list->next;
	}
	self->red = new_red_tab;
	return (0);
}
