/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:37:52 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:56:38 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if (n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
		}
	}
	else if (src > dest)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return ((unsigned char *)dest);
}

/*#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	(void)argc;
	unsigned char *res1 = ft_memmove(argv[1], argv[2], argv[3][0] - 48);
	unsigned char *res2 = memmove(argv[1], argv[2], argv[3][0] - 48);
	printf("mon memmove : %s\n", res1);
	printf("memmove officiel: %s", res2);
	return 0;
}*/
