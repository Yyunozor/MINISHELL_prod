/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:56 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:55:21 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

/*#include <stdio.h>
int main(int argc, char** argv)
{
	(void)argc;
	int res = ft_isalnum(argv[1][0]);
	printf("%d", res);
}*/
