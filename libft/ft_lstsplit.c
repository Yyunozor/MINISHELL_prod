/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:43:58 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/08 12:44:03 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstsplit_once(t_list **lst, int (*is_separator)(t_list *node))
{
	t_list	*lst_head;
	t_list	*lst_new;

	lst_head = *lst;
	lst_new = *lst;
	while (lst_new)
	{
		if (is_separator(lst_new))
		{
			*lst = lst_new->next;
			lst_new->next = NULL;
			return (lst_head);
		}
		lst_new = lst_new->next;
	}
	*lst = NULL;
	return (lst_head);
}

t_list	*ft_lstsplit(t_list *lst_current, int (*is_separator)(t_list *node))
{
	t_list	*newlst;
	t_list	*element;

	newlst = ft_lstnew(ft_lstsplit_once(&lst_current, is_separator));
	if (newlst == NULL)
		return (NULL);
	while (lst_current)
	{
		element = ft_lstnew(ft_lstsplit_once(&lst_current, is_separator));
		if (element == NULL)
			return (NULL);
		ft_lstadd_back(&newlst, element);
	}
	return (newlst);
}
