/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:40:13 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 13:00:52 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start || s[0] == '\0')
		len = 0;
	else if ((unsigned int)ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	tab = malloc(sizeof (char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = '\0';
	return (tab);
}
