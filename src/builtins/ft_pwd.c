/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include <unistd.h>

// pwd builtin: print current working directory
int	ft_pwd(t_scmd *scmd)
{
	char	cwd[1024];

	(void)scmd;
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}
