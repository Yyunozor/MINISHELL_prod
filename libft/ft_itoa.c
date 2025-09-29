/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:19:10 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 13:02:17 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*intmin(void)
{
	char	*tab;

	tab = malloc(sizeof(char) * 12);
	if (tab == NULL)
		return (NULL);
	tab[0] = '-';
	tab[1] = '2';
	tab[2] = '1';
	tab[3] = '4';
	tab[4] = '7';
	tab[5] = '4';
	tab[6] = '8';
	tab[7] = '3';
	tab[8] = '6';
	tab[9] = '4';
	tab[10] = '8';
	tab[11] = '\0';
	return (tab);
}

char	*malltab(int n, int *i)
{
	char	*tab;

	*i = 0;
	if (n == 0)
		*i += 1;
	if (n < 0)
	{
		n = n * -1;
		*i += 1;
	}
	while (n > 0)
	{
		n = n / 10;
		*i += 1;
	}
	*i += 1;
	tab = malloc(sizeof(char) * *i);
	if (tab == NULL)
		return (NULL);
	tab[*i - 1] = '\0';
	return (tab);
}

char	*filltabitoa(char *tab, int i, int n)
{
	int	neg;

	neg = 0;
	i = i - 2;
	if (n < 0)
	{
		tab[0] = '-';
		n = n * -1;
		neg = 1;
	}
	while (i >= (0 + neg))
	{
		tab[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	if (n == -2147483648)
	{
		tab = intmin();
		if (tab == NULL)
			return (NULL);
		return (tab);
	}
	tab = malltab(n, &i);
	if (tab == NULL)
		return (NULL);
	tab = filltabitoa(tab, i, n);
	return (tab);
}

/*#include <stdio.h>

int main(void)
{
	char	*res = ft_itoa(0);
	printf("%s", res);
	return (0);
}*/
