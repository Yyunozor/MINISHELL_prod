/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 05:08:08 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

// Return 1 if command name matches a supported builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

// Check if builtin can be executed in parent even with pipes (output-producing)
int	is_pipeable_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	return (0);
}

// Dispatch and execute builtin, return its exit status
int	execute_builtin(t_scmd *scmd)
{
	if (!scmd || !scmd->argv || !scmd->argv[0])
		return (1);
	if (ft_strncmp(scmd->argv[0], "echo", 4) == 0)
		return (ft_echo(scmd));
	if (ft_strncmp(scmd->argv[0], "cd", 2) == 0)
		return (ft_cd(scmd));
	if (ft_strncmp(scmd->argv[0], "pwd", 3) == 0)
		return (ft_pwd(scmd));
	if (ft_strncmp(scmd->argv[0], "export", 6) == 0)
		return (ft_export(scmd));
	if (ft_strncmp(scmd->argv[0], "unset", 5) == 0)
		return (ft_unset(scmd));
	if (ft_strncmp(scmd->argv[0], "env", 3) == 0)
		return (ft_env(scmd));
	if (ft_strncmp(scmd->argv[0], "exit", 4) == 0)
		return (ft_exit(scmd));
	return (1);
}

// Validate export/unset identifier: letters, digits, '_' and not starting
// with a digit
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Return pointer to value of var_name in env, or NULL
char	*get_env_var(char **env, char *var_name)
{
	int	i;
	int	len;

	if (!env || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
