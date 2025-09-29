/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:40:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/25 12:47:51 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

// Count how many variables remain after removing target
static int	count_remaining_vars(char **env, char *var_name, int var_len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var_name, var_len) == 0
				&& (env[i][var_len] == '=' || env[i][var_len] == '\0')))
			count++;
		i++;
	}
	return (count);
}

// Allocate new env array excluding removed variable
static char	**create_new_env(char **env, char *var_name, int var_len, int count)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var_name, var_len) == 0
				&& (env[i][var_len] == '=' || env[i][var_len] == '\0')))
		{
			new_env[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}

// Remove variable by name (if present) and return new array
char	**remove_env_var(char **env, char *var_name)
{
	int	var_len;
	int	count;

	if (!env || !var_name)
		return (env);
	var_len = ft_strlen(var_name);
	count = count_remaining_vars(env, var_name, var_len);
	return (create_new_env(env, var_name, var_len, count));
}
