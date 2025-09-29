/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/*
** Check if argument is a valid -n option for echo
** Valid: -n, -nn, -nnn, -nnnn, etc. (only 'n' characters after the dash)
** Invalid: -na, -n1, -nX, etc. (any non-'n' character)
*/
static int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	if (!arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// echo: print args separated by spaces
// any -n / -nn / -nnn ... suppresses trailing newline
int	ft_echo(t_scmd *scmd)
{
	int		i;
	int		newline;
	char	**argv;

	if (!scmd || !scmd->argv)
		return (1);
	argv = scmd->argv;
	i = 1;
	newline = 1;
	while (argv[i] && is_valid_n_option(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
