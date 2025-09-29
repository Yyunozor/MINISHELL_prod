/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:55:27 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 13:01:29 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*filltabtrim(char const *s1, char const *set, size_t i)
{
	size_t		start;
	size_t		end;
	char		*tab;

	start = i;
	while (s1[i] != '\0')
		i++;
	i--;
	while (i > 0 && checkset(set, s1[i]) != 0)
		i--;
	end = i;
	tab = malloc(sizeof(char) * (end - start + 2));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		tab[i++] = s1[start++];
	tab[i] = '\0';
	return (tab);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char		*tab;

	i = 0;
	while (s1[i] != '\0' && checkset(set, s1[i]) != 0)
		i++;
	if (i == ft_strlen(s1))
	{
		tab = malloc(sizeof(char) * 1);
		if (tab == NULL)
			return (NULL);
		tab[0] = '\0';
	}
	else
	{
		tab = filltabtrim(s1, set, i);
	}
	return (tab);
}

/*#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	char *res = ft_strtrim(argv[1], argv[2]);
	printf("%s", res);
	return 0;
}*/
