/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:43:18 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 03:37:38 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pars_init(t_pars_data *data, char **envp, char *line)
{
	data->lst_token = NULL;
	data->lst_simple_cmd = NULL;
	data->envp = envp;
	data->err_status = 0;
	if (line[0] == '\0')
	{
		free(line);
		return (1);
	}
	return (0);
}
