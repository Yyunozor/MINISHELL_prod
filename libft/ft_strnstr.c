/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 00:47:39 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:58:52 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (little[i] == '\0')
	{
		return (big);
	}
	while (big[i] != '\0' && i < len)
	{
		y = 0;
		while (little[y] == big[i + y] && (y + i) < len)
		{
			y++;
			if (little[y] == '\0' || little[y - 1] == '\0')
			{
				return (&big[i]);
			}
		}
		i++;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	(void)argc;
	char *res = ft_strnstr(argv[1], argv[2], argv[3][0] - 48);
	printf("%s", res);
	return 0;
}*/
