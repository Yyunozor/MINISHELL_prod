/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:48:55 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:12:16 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_expand_dollar
{
	char	*result;
	char	*name;
	char	*value;
	char	start;
}	t_expand_dollar;

typedef struct s_expand_view
{
	char	*newstr;
	char	*temp;
	size_t	i;
	char	quote;
}	t_expand_view;

char	*expand_str(char *str, char **envp, int last_status);
char	*expand_str_heredoc(char *str, char **envp, int last_status);

int		expand_quotes_check(t_token *token);
char	*expand_remove_quote(char *str);

char	*ft_get_env_value(char **envp, char *name);

#endif
