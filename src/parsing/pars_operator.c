/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:44:26 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:27:49 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	pars_operator_cleanup(t_pars_data *data)
{
	ft_lstclear(&data->lst_token, del_token);
	return (1);
}

static int	update_node_op(t_list **lst_prev, t_list **lst_current,
				 t_pars_data *data)
{
	t_list	*lst_new;
	t_list	*lst_temp_last;

	lst_new = lst_str_split((*lst_current)->token->str);
	if (lst_new == NULL)
		return (1);
	lst_temp_last = ft_lstlast(lst_new);
	lst_temp_last->next = (*lst_current)->next;
	if (*lst_prev)
		(*lst_prev)->next = lst_new;
	else
		data->lst_token = lst_new;
	ft_lstdelone(*lst_current, del_token);
	*lst_current = lst_temp_last;
	return (0);
}

static int	pars_operator_handle_node(t_pars_data *data, t_list **prev,
			t_list **current)
{
	if ((*current)->token->type == METACAR)
		return (update_node_op(prev, current, data));
	if ((*current)->token->type == ALPHABET)
		return (expand_quotes_check((*current)->token));
	return (0);
}

int	pars_operator(t_pars_data *data)
{
	t_list	*lst_current;
	t_list	*lst_prev;

	lst_current = data->lst_token;
	lst_prev = NULL;
	while (lst_current)
	{
		if (pars_operator_handle_node(data, &lst_prev, &lst_current))
			return (pars_operator_cleanup(data));
		lst_prev = lst_current;
		lst_current = lst_current->next;
	}
	return (0);
}
