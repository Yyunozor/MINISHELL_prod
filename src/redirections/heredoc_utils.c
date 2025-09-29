/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 07:45:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 17:22:43 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "heredoc_utils.h"
#include <errno.h>

int	heredoc_cleanup(int fd_pipe[2], char *line, int result)
{
	if (line)
		free(line);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	signals_set_interactive();
	return (result);
}

void	heredoc_write_and_free(int write_fd, char *line)
{
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

static int	process_heredoc_line(t_red *red, t_heredoc_ctx *ctx, char *line)
{
	if (ft_strlen(line) == ctx->delim_len
		&& !ft_strncmp(line, red->word, ctx->delim_len))
	{
		free(line);
		return (1);
	}
	if (heredoc_expand_line(red, &line, ctx->envp, ctx->exit_status))
		return (-1);
	heredoc_write_and_free(ctx->fd_pipe[1], line);
	return (0);
}

int	heredoc_collect_lines(t_red *red, t_heredoc_ctx *ctx)
{
	char	*line;
	int		result;

	g_signal_received = 0;
	while (1)
	{
		line = read_heredoc_line();
		if (line == NULL || g_signal_received == SIGINT)
		{
			if (line)
				free(line);
			return (heredoc_cleanup(ctx->fd_pipe, NULL, -1));
		}
		result = process_heredoc_line(red, ctx, line);
		if (result == 1)
			break ;
		if (result == -1)
			return (heredoc_cleanup(ctx->fd_pipe, NULL, 1));
	}
	return (0);
}