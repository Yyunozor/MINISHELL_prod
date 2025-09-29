/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:18:23 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 13:00:13 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = 0;
		i++;
	}
}

/*#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	(void)argc;
	ft_bzero(argv[1], argv[3][0] - 48);
	bzero(argv[2], argv[3][0] - 48);
	printf("mon bzero %s\n", argv[1]);
	printf("bzero officel %s", argv[2]);
}*/
