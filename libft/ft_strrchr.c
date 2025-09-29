/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:05:07 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:57:40 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)&str[i]);
		}
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	(void)argc;
	char *res = ft_strrchr(argv[1], argv[2][0]);
	printf("%s", res);
	return 0;
}*/
