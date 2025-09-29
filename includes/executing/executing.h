/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:25:20 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

typedef struct s_fd
{
	int	fd_saved_in;	//ok
	int	fd_saved_out;	//ok
	int	fd_prev;
	int	fd_pipe[2];
}	t_fd;

typedef struct s_exec_data
{
	t_list	*lst_simple_cmd;	//ok
	char	**envp;
	int		exit_status;
	t_fd	fd;
	int		is_interactive;
}	t_exec_data;

int	exec_init(t_exec_data *data, t_list *head, char **envp, int last_exit_status);
int	exec_pipeline(t_exec_data *data);
int	exec_simple_builtin(t_scmd *self, t_exec_data *data);

//pipeline
int	exec_child(t_scmd *self, t_exec_data *data);
int	exec_expansion(t_scmd *self);
int	exec_child_set_path(t_scmd *self, char **envp);
int	exec_parent(t_list *self, t_exec_data *data);
int	exec_parent_wait(t_exec_data *data);
size_t	exec_trim_empty_prefix(t_scmd *self);
void	exec_shift_trimmed_argv(t_scmd *self, size_t skipped);

#endif
