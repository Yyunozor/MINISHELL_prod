/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 04:14:48 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <errno.h>
#include <string.h>

static int	cd_error_message(char *arg)
{
	ft_putstr_fd("minishell: cd", 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

// Return pointer to HOME value or NULL
char	*get_home_directory(t_scmd *scmd)
{
	return (get_env_var(scmd->env, "HOME"));
}

// Change to HOME directory; update env on success
int	cd_to_home(t_scmd *scmd, char *old_pwd)
{
	char	*path;

	path = get_home_directory(scmd);
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	return (cd_to_path(scmd, path, old_pwd));
}

// Change to specified path; update env on success
int	cd_to_path(t_scmd *scmd, char *path, char *old_pwd)
{
	if (chdir(path) != 0)
		return (cd_error_message(path));
	return (update_pwd_vars(scmd, old_pwd));
}

// Update OLDPWD and PWD after successful directory change
int	update_pwd_vars(t_scmd *scmd, char *old_pwd)
{
	char	new_pwd[1024];

	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	scmd->env = update_env_var(scmd->env, "OLDPWD", old_pwd);
	scmd->env = update_env_var(scmd->env, "PWD", new_pwd);
	return (0);
}
