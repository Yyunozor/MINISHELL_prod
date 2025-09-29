/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_env_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 08:13:10 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 03:50:46 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_get_valueline(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (name + i + 1);
		i++;
	}
	return (NULL);
}

char	*ft_get_env_line(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i] && envp)
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name))
			&& (envp[i][ft_strlen(name)] == '=' || envp[i][ft_strlen(name)] == '\0'))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_get_env_value(char **envp, char *name)
{
	char	*value;
	char	*line;

	line = ft_get_env_line(envp, name);
	if (line == NULL)
		return (NULL);
	value = ft_get_valueline(line);
	if (value == NULL)
		return (NULL);
	return (value);
}
