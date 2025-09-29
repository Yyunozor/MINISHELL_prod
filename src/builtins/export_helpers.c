/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

// Simple bubble sort of environment pointer array (in-place)
void	sort_env_array(char **sorted_env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(sorted_env[j], sorted_env[j + 1],
					ft_strlen(sorted_env[j])) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Print export listing recreating declare -x format
void	print_export_vars(char **sorted_env)
{
	char	*equal_pos;
	int		i;

	i = 0;
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equal_pos = ft_strchr(sorted_env[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
			*equal_pos = '=';
		}
		else
		{
			ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
}

// Handle export of NAME=VALUE form
int	export_with_value(t_scmd *scmd, char *arg, char *equal_pos)
{
	char	*var_name;
	char	*var_value;

	*equal_pos = '\0';
	var_name = arg;
	var_value = equal_pos + 1;
	if (!is_valid_identifier(var_name))
	{
		write(2, "minishell: export: `", 21);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		*equal_pos = '=';
		return (1);
	}
	scmd->env = update_env_var(scmd->env, var_name, var_value);
	*equal_pos = '=';
	return (0);
}

// Handle export of NAME (no value given) without overwriting existing value
int	export_without_value(t_scmd *scmd, char *arg)
{
	char	*existing;

	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 21);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	existing = get_env_var(scmd->env, arg);
	if (existing != NULL)
		return (0);
	scmd->env = update_env_var(scmd->env, arg, NULL);
	return (0);
}
