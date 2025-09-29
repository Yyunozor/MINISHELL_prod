/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:00:00 by GitHub Copilot   #+#    #+#             */
/*   Updated: 2024/10/30 00:00:00 by GitHub Copilot  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	exec_trim_empty_prefix(t_scmd *self)
{
	size_t	count;

	count = 0;
	while (self->argv[count] && self->argv[count][0] == '\0')
	{
		free(self->argv[count]);
		self->argv[count] = NULL;
		count++;
	}
	return (count);
}

void	exec_shift_trimmed_argv(t_scmd *self, size_t skipped)
{
	size_t	y;

	y = 0;
	while (self->argv[skipped + y])
	{
		self->argv[y] = self->argv[skipped + y];
		self->argv[skipped + y] = NULL;
		y++;
	}
	while (y < self->nbr_of_argv)
	{
		self->argv[y] = NULL;
		y++;
	}
}
