/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 05:14:51 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <stdlib.h>
#include <limits.h>

// Return 1 if string is [sign] + digits
static int	is_numeric_string(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// Return 1 on overflow while parsing positive part into long
static int	check_overflow(char *str)
{
	long	result;
	int		i;

	if (!str)
		return (1);
	result = 0;
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

// exit builtin: terminate shell; validates numeric argument and overflow
int	ft_exit(t_scmd *scmd)
{
	int	status;

	if (scmd && scmd->is_interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
	status = 0;
	if (scmd)
		status = scmd->exit_status;
	if (scmd && scmd->argv && scmd->argv[1])
	{
		if (!is_numeric_string(scmd->argv[1]) || check_overflow(scmd->argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(scmd->argv[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(255);
		}
		if (scmd->argv[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		status = ft_atoi(scmd->argv[1]);
	}
	exit(status & 0xFF);
}
