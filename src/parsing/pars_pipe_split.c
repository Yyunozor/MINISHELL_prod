/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:44:11 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 03:37:38 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_pipe(t_list *lst_current)
{
	return (!ft_strncmp(lst_current->token->str, "|", 2));
}

//free apres return 1
int	pars_pipe_check(t_list *lst_current, t_pars_data *data)
{
	if (is_pipe(lst_current->lst))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		ft_lstclear(&data->lst_simple_cmd, del_lst_token);
		data->err_status = 2;
		return (1);
	}
	while (lst_current)
	{
		if (is_pipe(lst_current->lst))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			ft_lstclear(&data->lst_simple_cmd, del_lst_token);
			data->err_status = 2;
			return (1);
		}
		lst_current = lst_current->next;
	}
	return (0);
}

//pas obligatoire mais + secure
//void	pars_pipe_remove(t_list *lst_lst_current)
//{
//	return ;
//	t_list	*lst_current;
//	t_list	*lst_prev;
//
//	while (lst_lst_current)
//	{
//		lst_current = lst_lst_current->lst;
//		lst_prev = NULL;
//		while (lst_current)
//		{
//			if (is_pipe(lst_current))
//			{
//				lst_prev->next = NULL;
//				ft_lstdelone(lst_current, del_token);
//			}
//			lst_prev = lst_current;
//			lst_current = lst_current->next;
//		}
//		lst_lst_current = lst_lst_current->next;
//	}
//}

int	pars_pipe_split(t_pars_data *data)
{
	data->lst_simple_cmd = ft_lstsplit(data->lst_token, &is_pipe);
	if (data->lst_simple_cmd == NULL)
	{
		del_lst_token(data->lst_simple_cmd);
		data->err_status = 2;
		return (1);
	}
	if (pars_pipe_check(data->lst_simple_cmd, data))
		return (1);
	return (0);
}
