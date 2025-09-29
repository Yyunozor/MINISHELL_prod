/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:34:03 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "pars_metacar.h"
# include "pars_operator.h"

typedef struct s_shell			t_shell;

struct	s_token
{
	int		type;
	char	*str;
};

typedef struct s_pars_data
{
	t_list	*lst_token;
	t_list	*lst_simple_cmd;
	char	**envp;
	int		err_status; // 0 ok, otherwise propagate to shell->last_exit_status
}	t_pars_data;

int		pars_init(t_pars_data *data, char **envp, char *line);
int		pars_metacar(char *str, t_pars_data *data);
int		pars_operator(t_pars_data *data);
int		pars_space(t_pars_data *data);
int		pars_pipe_split(t_pars_data *data);
int		pars_scmd(t_pars_data *data);

char	*parsing_get_line(t_shell *shell);
int		parsing_handle_line(t_shell *shell, char *line);
int		parsing_execute(t_shell *shell, t_pars_data *data, char *line);

//utils
void	print_lst(t_list *lst);
void	print_lst_double(t_list *lst);
void	print_lst_scmd(t_list *lst);
void	free_list(t_list **lst);

void	del_token(void *ptr);
void	del_token2(void *ptr);
void	del_lst_token(void *token_lst);
void	del_lst_scmd(void *ptr);
void	clear_simple_cmd_mixed(t_list **lst);

//scmd fill
int		scmd_parse_red(t_scmd *self, t_list *token_list);
int		scmd_parse_argv(t_scmd *self, t_list *token_list);
void	scmd_parse_command_path(t_scmd *self);
void	scmd_parse_env(t_scmd *self, char **envp);
t_scmd	*scmd_create(t_list *token_list, t_pars_data *data);

#endif
