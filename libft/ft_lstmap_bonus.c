/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:54:07 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:52:08 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*newcontent;
	t_list	*newelement;
	t_list	*newlst;

	newlst = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		newelement = malloc(sizeof(t_list));
		if (newelement == NULL)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		newelement->content = newcontent;
		newelement->next = NULL;
		ft_lstadd_back(&newlst, newelement);
		lst = lst->next;
	}
	return (newlst);
}
