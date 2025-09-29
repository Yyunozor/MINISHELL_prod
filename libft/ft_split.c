/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:57:51 by jsurian           #+#    #+#             */
/*   Updated: 2025/09/21 11:44:32 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freeall(char **tab, int i)
{
	int	d;

	d = 0;
	while (d < i)
	{
		free(tab[d]);
		tab[d] = NULL;
		d++;
	}
	free(tab);
}

int	lenchaine(char const *s, char c, int *y)
{
	int	len;

	len = 0;
	if (c == '\0')
	{
		while (s[*y] != '\0')
		{
			len++;
			*y += 1;
		}
		return (len);
	}
	while (s[*y] == c)
		*y += 1;
	while (s[*y] != '\0' && s[*y] != c)
	{
		if (s[*y] != c)
			len++;
		*y += 1;
	}
	while (s[*y] == c)
		*y += 1;
	return (len);
}

char	**ft_tab(char const *s, char c, int sizemalloc)
{
	char	**tab;
	int		i;
	int		y;
	int		len;

	i = 0;
	y = 0;
	tab = malloc(sizeof (char *) * sizemalloc);
	if (tab == NULL)
		return (NULL);
	while (i < sizemalloc - 1)
	{
		len = lenchaine(s, c, &y) + 1;
		tab[i] = malloc(sizeof(char) * len);
		if (tab[i] == NULL)
		{
			freeall(tab, i);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	filltab(char const *s, char c, char **tab)
{
	int	i;
	int	y;
	int	sizemalloc;

	i = 0;
	y = 0;
	sizemalloc = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			y = 0;
			while (s[i] != c && s[i] != '\0')
				tab[sizemalloc][y++] = s[i++];
			tab[sizemalloc][y] = '\0';
			sizemalloc++;
		}
		else
			i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		sizemalloc;
	char	**tab;

	i = 0;
	sizemalloc = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			sizemalloc++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	sizemalloc = sizemalloc + 1;
	tab = ft_tab(s, c, sizemalloc);
	if (tab == NULL)
		return (NULL);
	filltab(s, c, tab);
	return (tab);
}

/*#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	char **res;
	res	= ft_split(argv[1], argv[2][0]);
	int i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return 0;
}*/
