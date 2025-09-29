/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:05:39 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/17 12:59:04 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	resultat;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10;
		nb = str[i] - '0';
		resultat = resultat + nb;
		i++;
	}
	return (resultat * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char **argv)
{
	(void)argc;
	int result1 = ft_atoi(argv[1]);
	int result2 = atoi(argv[1]);
	printf("Output:%d\n", result1);
	printf("output2:%d\n", result2);
	return(0);
}*/
