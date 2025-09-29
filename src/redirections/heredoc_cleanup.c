/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:20:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 17:22:43 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "heredoc_utils.h"
#include <errno.h>

static int	read_char_from_stdin(char *line, int *i)
{
	char	c;
	int		read_result;

	read_result = read(STDIN_FILENO, &c, 1);
	if (read_result == -1)
	{
		if (errno == EINTR && g_signal_received == SIGINT)
			return (-1);
		return (0);
	}
	if (read_result == 0)
		return (1);
	if (c == '\n')
		return (2);
	if (*i >= 1023)
		return (2);
	line[(*i)++] = c;
	return (3);
}

static char	*handle_read_status(char *line, int status, int i)
{
	if (status == -1)
	{
		free(line);
		return (NULL);
	}
	if (status == 1 && i == 0)
	{
		free(line);
		return (NULL);
	}
	if (status == 1 || status == 2)
	{
		line[i] = '\0';
		return (line);
	}
	return (line);
}

char	*read_heredoc_line(void)
{
	char	*line;
	int		i;
	int		status;
	char	*result;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	write(STDOUT_FILENO, "> ", 2);
	while (1)
	{
		status = read_char_from_stdin(line, &i);
		result = handle_read_status(line, status, i);
		if (status != 0 && status != 3)
			return (result);
		if (status == 0)
			continue;
	}
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