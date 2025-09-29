/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian <jsurian@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:19:14 by jsurian           #+#    #+#             */
/*   Updated: 2024/10/28 13:28:48 by jsurian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	test(int *n, int fd)
{
	if (*n == 0)
	{
		write(fd, "0", 1);
	}
	if (*n < 0)
	{
		write(fd, "-", 1);
		*n = *n * -1;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	stock[13];

	i = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		test(&n, fd);
		while (n != 0)
		{
			stock[i] = n % 10 + 48;
			n = n / 10;
			i++;
		}
		i--;
		while (i >= 0)
		{
			write(fd, &stock[i], 1);
			i--;
		}
	}
}

/*int main(void)
{
	ft_putnbr_fd(-123, 1);
	return (0);
}*/
