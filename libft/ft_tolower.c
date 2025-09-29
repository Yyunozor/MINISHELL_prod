/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 05:20:18 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:57:28 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
	}
	return (c);
}

/*#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	(void)argc;
	int res = ft_tolower(argv[1][0]);
	printf("%c", res);
	return 0;
}*/
