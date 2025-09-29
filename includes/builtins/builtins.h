/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:05:43 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/25 12:47:51 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../libft/libft.h"

// Forward declaration to avoid circular dependency
typedef struct s_scmd	t_scmd;

// Builtins functions with unified signature - only t_scmd parameter needed
int		ft_echo(t_scmd *scmd);
int		ft_cd(t_scmd *scmd);
int		ft_pwd(t_scmd *scmd);
int		ft_export(t_scmd *scmd);
int		ft_unset(t_scmd *scmd);
int		ft_env(t_scmd *scmd);
int		ft_exit(t_scmd *scmd);

// Utility functions
int		is_builtin(char *cmd);
int		is_pipeable_builtin(char *cmd);
int		execute_builtin(t_scmd *scmd);
char	**update_env_var(char **env, char *var_name, char *var_value);
char	**add_env_var(char **env, char *new_var);
char	**remove_env_var(char **env, char *var_name);
char	*get_env_var(char **env, char *var_name);
int		is_valid_identifier(char *str);
void	sort_env_array(char **sorted_env, int count);
void	print_export_vars(char **sorted_env);
int		export_with_value(t_scmd *scmd, char *arg, char *equal_pos);
int		export_without_value(t_scmd *scmd, char *arg);
int		cd_to_home(t_scmd *scmd, char *old_pwd);
int		cd_to_path(t_scmd *scmd, char *path, char *old_pwd);
int		update_pwd_vars(t_scmd *scmd, char *old_pwd);
char	*get_home_directory(t_scmd *scmd);

#endif
