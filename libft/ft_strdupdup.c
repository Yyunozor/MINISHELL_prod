/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:57:41 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/17 16:53:20 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//ne pas oublier de free le cpy[i] = NULL
void	ft_freedupdup(char **cpy, int i)
{
	int	y;

	y = 0;
	while (y < i)
	{
		free(cpy[y]);
		y++;
	}
	free(cpy);
}

char	**ft_strdupdup(const char **str)
{
	int		i;
	char	**cpy;

	i = 0;
	while (str[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		cpy[i] = ft_strdup(str[i]);
		if (cpy[i] == NULL)
			return (ft_freedupdup(cpy, i), NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
