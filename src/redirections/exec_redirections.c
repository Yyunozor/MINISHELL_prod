/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:17:16 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:27:49 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	report_open_error(char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (1);
}

static int	exec_open_redirection(t_red *red, int flags,
		int mode, int target_fd)
{
	int	fd;

	fd = open(red->word, flags, mode);
	if (fd == -1)
		return (report_open_error(red->word));
	if (dup2(fd, target_fd) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	exec_red_heredoc(t_red *red)
{
	if (dup2(red->fd_heredoc, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 heredoc");
		return (1);
	}
	close(red->fd_heredoc);
	return (0);
}

static int	exec_apply_redirection(t_red *red)
{
	int	flags;
	int	mode;
	int	target;

	if (red->type == RED_HEREDOC)
		return (exec_red_heredoc(red));
	flags = O_RDONLY;
	mode = 0;
	target = STDIN_FILENO;
	if (red->type != RED_INPUT)
	{
		target = STDOUT_FILENO;
		mode = 0644;
		if (red->type == RED_OUTPUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (red->type == RED_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	return (exec_open_redirection(red, flags, mode, target));
}

int	exec_redirections(t_scmd *self)
{
	size_t	i;

	i = 0;
	while (i < self->nbr_of_red)
	{
		if (exec_apply_redirection(&self->red[i]))
			return (1);
		i++;
	}
	return (0);
}
