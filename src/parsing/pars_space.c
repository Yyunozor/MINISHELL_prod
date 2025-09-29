/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:24:34 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/25 19:51:26 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	del_token_space(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	free(token->str);
	free(token);
}

int	put_space_away(t_list **lst_prev, t_list **lst_current, t_pars_data *data)
{
	if (*lst_prev)
	{
		(*lst_prev)->next = (*lst_current)->next;
		ft_lstdelone(*lst_current, del_token_space);
		(*lst_current) = (*lst_prev);
		return (0);
	}
	else
	{
		data->lst_token = (*lst_current)->next;
		ft_lstdelone(*lst_current, del_token_space);
		(*lst_current) = data->lst_token;
		return (1);
	}
}

int	pars_space(t_pars_data *data)
{
	t_list	*lst_current;
	t_list	*lst_prev;

	lst_current = data->lst_token;
	lst_prev = NULL;
	while (lst_current)
	{
		if (lst_current->token->type == ESPACE)
			if (put_space_away(&lst_prev, &lst_current, data))
				continue ;
		lst_prev = lst_current;
		lst_current = lst_current->next;
	}
	if (data->lst_token == NULL)
		return (1);
	return (0);
}
