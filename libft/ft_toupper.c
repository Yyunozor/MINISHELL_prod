/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 05:10:24 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:57:21 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
	}
	return (c);
}

/*#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	(void)argc;
	char res = ft_toupper(argv[1][0]);
	printf("%c", res);
	return 0;
}*/
