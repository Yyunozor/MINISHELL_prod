/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 04:44:44 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:57:10 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = 0;
	len_dst = 0;
	i = 0;
	len_src = ft_strlen(src);
	while (dst[len_dst] != '\0' && len_dst < size)
		len_dst++;
	if (size <= len_dst)
		return (size + len_src);
	else
	{
		len_src = len_dst + len_src;
		while (len_dst < size - 1 && src[i] != '\0')
		{
			dst[len_dst] = src[i];
			len_dst++;
			i++;
		}
		dst[len_dst] = '\0';
	}
	return (len_src);
}

/*#include <stdio.h>
int main(void)
{
	char dst[10000] = "Hello";
	char src[1000] = "World";
	size_t size = 38;
	char dst2[10000] = "Hello";
	char src2[1000] = "World";


	int res = ft_strlcat(dst, src, size);
	int res2 = strlcat(dst2, src2, size);
	printf("ma fonction : %d\n", res);
	printf("dst : %s\n", dst);
	printf("fonction officiel : %d\n", res2);
	printf("dst : %s", dst2);
	return 0;
}*/
