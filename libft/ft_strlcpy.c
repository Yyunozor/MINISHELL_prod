/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:57:54 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:56:52 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (src[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (y < size - 1 && src[y] != '\0')
	{
		dest[y] = src[y];
		y++;
	}
	dest[y] = '\0';
	return (i);
}

/*#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	(void)argc;
	int res1 = ft_strlcpy(argv[1], argv[2], argv[3][0] - 48);
	printf("longueur src : %d\n", res1);
	printf("dest : %s", argv[1]);
}*/
