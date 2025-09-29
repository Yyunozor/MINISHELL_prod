/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/26 09:04:50 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <stdio.h>
#include <unistd.h>

// Print environment variables in sorted order (declare -x style)
static void	print_sorted_export_env(char **env)
{
	char	**sorted_env;
	int		i;
	int		count;

	if (!env)
		return ;
	count = 0;
	while (env[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return ;
	i = 0;
	while (i < count)
	{
		sorted_env[i] = env[i];
		i++;
	}
	sorted_env[count] = NULL;
	sort_env_array(sorted_env, count);
	print_export_vars(sorted_env);
	free(sorted_env);
}

// Handle one export argument (with or without '=')
static int	export_variable(t_scmd *scmd, char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		return (export_with_value(scmd, arg, equal_pos));
	else
		return (export_without_value(scmd, arg));
}

// export builtin: list when no args; else set/mark variables
int	ft_export(t_scmd *scmd)
{
	int	i;
	int	ret;

	if (!scmd || !scmd->argv)
		return (1);
	if (!scmd->argv[1])
	{
		print_sorted_export_env(scmd->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (scmd->argv[i])
	{
		if (export_variable(scmd, scmd->argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
