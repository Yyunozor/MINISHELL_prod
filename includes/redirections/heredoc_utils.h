/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 07:45:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 17:22:43 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_UTILS_H
# define HEREDOC_UTILS_H

typedef struct s_red					t_red;
typedef struct s_exec_data				 t_exec_data;
typedef struct s_heredoc_ctx			 t_heredoc_ctx;

struct s_heredoc_ctx
{
	int		*fd_pipe;
	char	**envp;
	size_t	delim_len;
	int		exit_status;
};

int			heredoc_cleanup(int fd_pipe[2], char *line, int result);
int			heredoc_expand_line(t_red *red, char **line,
			char **envp, int exit_status);
void		heredoc_write_and_free(int write_fd, char *line);
void		exec_cleanup_heredocs(t_exec_data *data);
int			heredoc_collect_lines(t_red *red, t_heredoc_ctx *ctx);
char		*read_heredoc_line(void);

#endif
