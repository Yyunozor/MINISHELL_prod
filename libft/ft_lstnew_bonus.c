/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:35:47 by jsurian           #+#    #+#             */
/*   Updated: 2025/09/28 03:37:38 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content1)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	element->content = content1;
	element->is_scmd = 0;
	element->next = NULL;
	return (element);
}
