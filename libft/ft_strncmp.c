/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:50 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:58:07 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

/*#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	int res = ft_strncmp(argv[1], argv[2], argv[3][0] - 48);
	int res2 = strncmp(argv[1], argv[2], argv[3][0] - 48);
	printf("ma fonction : %d\n", res);
	printf("fonction officielle : %d", res2);
	return 0;
}*/
