/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 05:25:47 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:57:57 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	(void)argc;
	char *res = ft_strchr(argv[1], argv[2][0]);
	printf("%s", res);
	return 0;
}*/
