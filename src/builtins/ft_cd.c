/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

static char	*get_oldpwd_directory(t_scmd *scmd)
{
	return (get_env_var(scmd->env, "OLDPWD"));
}

// Handle `cd -`: jump to OLDPWD, print it, update PWD/OLDPWD
static int	handle_cd_dash(t_scmd *scmd, char *old_pwd)
{
	char	*oldpwd_path;

	oldpwd_path = get_oldpwd_directory(scmd);
	if (!oldpwd_path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (cd_to_path(scmd, oldpwd_path, old_pwd) != 0)
		return (1);
	ft_putendl_fd(oldpwd_path, 1);
	return (0);
}

// Main cd builtin: no arg -> HOME, '-' -> OLDPWD, else specified path
int	ft_cd(t_scmd *scmd)
{
	char	old_pwd[1024];

	if (!scmd || !scmd->argv)
		return (1);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (!scmd->argv[1])
		return (cd_to_home(scmd, old_pwd));
	else if (ft_strncmp(scmd->argv[1], "-", 2) == 0)
		return (handle_cd_dash(scmd, old_pwd));
	else
		return (cd_to_path(scmd, scmd->argv[1], old_pwd));
}
