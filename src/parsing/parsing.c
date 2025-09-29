/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:35:14 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parsing(t_shell *shell)
{
	char		*line;
	t_pars_data	data;

	line = parsing_get_line(shell);
	if (parsing_handle_line(shell, line))
		return (1);
	if (parsing_execute(shell, &data, line))
		return (1);
	free(line);
	return (0);
}
