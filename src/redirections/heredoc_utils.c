/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 07:45:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 13:55:14 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "heredoc_utils.h"

int	heredoc_cleanup(int fd_pipe[2], char *line, int result)
{
	if (line)
		free(line);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	signals_set_interactive();
	return (result);
}

int	heredoc_expand_line(t_red *red, char **line, char **envp,
		int exit_status)
{
	char	*expanded;

	if (red->quoted_heredoc)
		return (0);
	expanded = expand_str_heredoc(*line, envp, exit_status);
	if (expanded == NULL)
	{
		*line = NULL;
		return (1);
	}
	*line = expanded;
	return (0);
}

void	heredoc_write_and_free(int write_fd, char *line)
{
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

void	exec_cleanup_heredocs(t_exec_data *data)
{
	t_list	*lst_current;
	size_t	i;

	lst_current = data->lst_simple_cmd;
	while (lst_current)
	{
		i = 0;
		while (i < lst_current->scmd->nbr_of_red)
		{
			if (lst_current->scmd->red[i].type == RED_HEREDOC
				&& lst_current->scmd->red[i].fd_heredoc != -1)
			{
				close(lst_current->scmd->red[i].fd_heredoc);
				lst_current->scmd->red[i].fd_heredoc = -1;
			}
			i++;
		}
		lst_current = lst_current->next;
	}
}

int	heredoc_collect_lines(t_red *red, t_heredoc_ctx *ctx)
{
	char	*line;

	while (1)
	{
		if (g_signal_received == SIGINT)
			return (heredoc_cleanup(ctx->fd_pipe, NULL, -1));
		line = readline("> ");
		if (g_signal_received == SIGINT)
		{
			if (line)
				free(line);
			return (heredoc_cleanup(ctx->fd_pipe, NULL, -1));
		}
		if (line == NULL) /* EOF (Ctrl+D) */
			return (heredoc_cleanup(ctx->fd_pipe, NULL, -1));
		if (ft_strlen(line) == ctx->delim_len 
			&& !ft_strncmp(line, red->word, ctx->delim_len))
		{
			free(line);
			break ;
		}
		if (heredoc_expand_line(red, &line, ctx->envp, ctx->exit_status))
			return (heredoc_cleanup(ctx->fd_pipe, NULL, 1));
		heredoc_write_and_free(ctx->fd_pipe[1], line);
	}
	return (0);
}
