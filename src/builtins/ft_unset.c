/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 03:50:46 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <stdio.h>
#include <unistd.h>

// unset builtin: remove each valid identifier from the environment
int	ft_unset(t_scmd *scmd)
{
	int	i;
	int	ret;

	if (!scmd || !scmd->argv)
		return (1);
	if (!scmd->argv[1])
		return (0);
	ret = 0;
	i = 1;
	while (scmd->argv[i])
	{
		if (!is_valid_identifier(scmd->argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(scmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
			scmd->env = remove_env_var(scmd->env, scmd->argv[i]);
		i++;
	}
	return (ret);
}
