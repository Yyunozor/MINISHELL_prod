/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:39:11 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:56:03 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = c;
		i++;
	}
	return (str);
}

/*#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	(void) argc;
	void *resultat1 = ft_memset(argv[1], argv[2][0], argv[3][0] - '0');
	void *resultat2 = memset(argv[1], argv[2][0], argv[3][0] - '0');
	printf("mon memset %s\n", (unsigned char*)resultat1);
	printf("memset officel %s", (unsigned char*)resultat2);
}*/
