/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <unistd.h>

// env builtin: print variables containing '='; rejects extra args
int	ft_env(t_scmd *scmd)
{
	int	i;

	if (!scmd || !scmd->env)
		return (1);
	if (scmd->argv[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(scmd->argv[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (127);
	}
	i = 0;
	while (scmd->env[i] != NULL)
	{
		if (ft_strchr(scmd->env[i], '='))
		{
			ft_putstr_fd(scmd->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
