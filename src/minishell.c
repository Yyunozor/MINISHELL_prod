/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:46:33 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 08:42:23 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	shell_init(t_shell *shell, char **envp)
{
	int		shell_lvl;
	char	**temp;

	shell->head = NULL;
	shell->envp = ft_strdupdup((const char **)envp);
	if (shell->envp == NULL)
		return (1);
	shell->last_exit_status = 0;
	shell->is_interactive = isatty(STDIN_FILENO);
	shell->stdout_isatty = isatty(STDOUT_FILENO);
	shell_lvl = ft_atoi(ft_get_env_value(shell->envp, "SHLVL"));
	shell_lvl++;
	temp = update_env_var(shell->envp, "SHLVL", ft_itoa(shell_lvl));
	if (!temp)
	{
		ft_split_free(shell->envp);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1)
		return (0);
	(void)argv;
	if (shell_init(&shell, envp))
		return (1);
	signals_set_interactive();
	while (1)
	{
		if (parsing(&shell))
			continue ;
		if (executing(&shell))
			continue ;
	}
	if (shell.head)
		ft_lstclear(&shell.head, del_lst_scmd);
	rl_clear_history();
	return (shell.last_exit_status);
}
