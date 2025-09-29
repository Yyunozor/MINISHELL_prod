/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:51:01 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_scmd	*scmd_abort(t_scmd *cmd)
{
	if (cmd->red)
		free(cmd->red);
	free(cmd);
	return (NULL);
}

t_scmd	*scmd_create(t_list *token_list, t_pars_data *data)
{
	t_scmd	*new_scmd;

	(void)data;
	new_scmd = malloc(sizeof(t_scmd));
	if (new_scmd == NULL)
		return (NULL);
	new_scmd->red = NULL;
	new_scmd->argv = NULL;
	new_scmd->command_path = NULL;
	new_scmd->exit_status = 0;
	new_scmd->is_interactive = 0;
	if (scmd_parse_red(new_scmd, token_list))
		return (scmd_abort(new_scmd));
	if (scmd_parse_argv(new_scmd, token_list))
		return (scmd_abort(new_scmd));
	scmd_parse_command_path(new_scmd);
	scmd_parse_env(new_scmd, data->envp);
	return (new_scmd);
}

int	pars_scmd(t_pars_data *data)
{
	t_list	*lst_cursor;
	t_scmd	*cmd;

	lst_cursor = data->lst_simple_cmd;
	while (lst_cursor)
	{
		cmd = scmd_create(lst_cursor->lst, data);
		if (!cmd)
		{
			clear_simple_cmd_mixed(&data->lst_simple_cmd);
			data->err_status = 2;
			return (1);
		}
		ft_lstclear(&(lst_cursor->lst), del_token2);
		lst_cursor->content = cmd;
		lst_cursor->is_scmd = 1;
		lst_cursor = lst_cursor->next;
	}
	return (0);
}
