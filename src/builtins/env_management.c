/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/25 22:01:01 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

// Append new VAR=VALUE string to environment array
char	**add_env_var(char **env, char *new_var)
{
	char	**new_env;
	int		len;
	int		j;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (env);
	j = 0;
	while (j < len)
	{
		new_env[j] = env[j];
		j++;
	}
	new_env[j] = new_var;
	new_env[j + 1] = NULL;
	free(env);
	return (new_env);
}

// Build VAR=VALUE string (value optional); returns allocated string
static char	*build_new_var(char *var_name, char *var_value)
{
	char	*base;
	char	*new_var;

	if (!var_value)
	{
		return (ft_strdup(var_name));
	}
	base = ft_strjoin(var_name, "=");
	if (!base)
		return (NULL);
	new_var = ft_strjoin(base, var_value);
	free(base);
	return (new_var);
}

// Replace existing var if found; else append it
static char	**replace_or_add_env(char **env, char *var_name, char *new_var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& (env[i][ft_strlen(var_name)] == '='
			|| env[i][ft_strlen(var_name)] == '\0'))
		{
			free(env[i]);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	return (add_env_var(env, new_var));
}

// Set or create an environment variable
char	**update_env_var(char **env, char *var_name, char *var_value)
{
	char	*new_var;

	if (!env || !var_name)
		return (env);
	new_var = build_new_var(var_name, var_value);
	if (!new_var)
		return (env);
	return (replace_or_add_env(env, var_name, new_var));
}

// remove_env_var and its helpers moved to env_remove.c to satisfy norm limits
