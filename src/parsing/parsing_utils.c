/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:30:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*read_shell_line(t_shell *shell)
{
	char	*line;

	if (shell->is_interactive)
		return (readline("minishell % "));
	if (shell->stdout_isatty)
		ft_putstr_fd("minishell % ", STDOUT_FILENO);
	line = readline("");
	return (line);
}

char	*parsing_get_line(t_shell *shell)
{
	char	*line;

	line = read_shell_line(shell);
	if (line == NULL)
		exit(shell->last_exit_status);
	if (g_signal_received == SIGINT)
	{
		shell->last_exit_status = 128 + SIGINT;
		g_signal_received = 0;
	}
	return (line);
}

int	parsing_handle_line(t_shell *shell, char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		return (1);
	}
	add_history(line);
	if (shell->head)
	{
		ft_lstclear(&shell->head, del_lst_scmd);
		shell->head = NULL;
	}
	return (0);
}

static int	handle_parsing_error(t_shell *shell, t_pars_data *data, char *line)
{
	if (data->err_status)
		shell->last_exit_status = data->err_status;
	free(line);
	return (1);
}

int	parsing_execute(t_shell *shell, t_pars_data *data, char *line)
{
	if (pars_init(data, shell->envp, line))
		return (1);
	if (pars_metacar(line, data))
		return (handle_parsing_error(shell, data, line));
	if (pars_operator(data))
		return (handle_parsing_error(shell, data, line));
	if (pars_space(data))
		return (handle_parsing_error(shell, data, line));
	if (pars_pipe_split(data))
		return (handle_parsing_error(shell, data, line));
	if (pars_scmd(data))
		return (handle_parsing_error(shell, data, line));
	shell->head = data->lst_simple_cmd;
	return (0);
}
