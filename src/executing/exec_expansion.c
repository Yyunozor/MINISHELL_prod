/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:32:18 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	exec_expansion_argv(t_scmd *self)
{
	size_t	i;
	char	*expanded;

	i = 0;
	while (self->argv[i])
	{
		expanded = expand_str(self->argv[i], self->env, self->exit_status);
		if (expanded == NULL)
			return (1);
		expanded = expand_remove_quote(expanded);
		if (expanded == NULL)
			return (1);
		self->argv[i] = expanded;
		i++;
	}
	return (0);
}

static int	exec_expansion_red(t_scmd *self)
{
	size_t	i;
	char	*expanded;

	i = 0;
	while (i < self->nbr_of_red)
	{
		expanded = expand_str(self->red[i].word, self->env, self->exit_status);
		if (expanded == NULL)
			return (1);
		expanded = expand_remove_quote(expanded);
		if (expanded == NULL)
			return (1);
		self->red[i].word = expanded;
		i++;
	}
	return (0);
}

static int	exec_remove_null_argv(t_scmd *self)
{
	size_t	skipped;

	if (!self->argv)
		return (0);
	skipped = exec_trim_empty_prefix(self);
	if (skipped == 0)
		return (0);
	if (!self->argv[skipped])
	{
		self->argv[0] = NULL;
		return (0);
	}
	exec_shift_trimmed_argv(self, skipped);
	return (0);
}

int	exec_expansion(t_scmd *self)
{
	if (exec_expansion_argv(self))
		return (1);
	if (exec_expansion_red(self))
		return (1);
	if (exec_remove_null_argv(self))
		return (1);
	return (0);
}
