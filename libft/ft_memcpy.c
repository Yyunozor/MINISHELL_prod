/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:13:13 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:56:25 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	(void)argc;
	unsigned char *res1 = ft_memcpy(argv[1], argv[2], argv[3][0] - 48);
	unsigned char *res2 = memcpy(argv[1], argv[2], argv[3][0] - 48);
	printf("mon memcpy : %s\n", res1);
	printf("memcpy officiel: %s", res2);
	return 0;
}*/
