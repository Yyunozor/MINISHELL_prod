/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:47:01 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

static void	expand_str_handle_quote(char *str, t_expand_view *view)
{
	char	*fragment;

	if (view->quote == 0)
		view->quote = str[view->i];
	else if (view->quote == str[view->i])
		view->quote = 0;
	fragment = ft_substr(str, view->i, 1);
	view->newstr = ft_strjoin_free(view->newstr, fragment);
	view->i++;
}

char	*expand_dollar(char *str, size_t *i, char **envp, int last_status)
{
	t_expand_dollar	v;

	*i += 1;
	if (str[*i] == '?')
	{
		*i += 1;
		v.result = ft_itoa(last_status);
		return (v.result);
	}
	if (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		v.start = *i;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			*i += 1;
		v.name = ft_substr(str, v.start, *i - v.start);
		v.value = ft_get_env_value(envp, v.name);
		free(v.name);
		if (v.value != NULL)
			return (ft_strdup(v.value));
		return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

char	*expand_str_heredoc(char *str, char **envp, int last_status)
{
	t_expand_view	v;
	char			*fragment;

	v.i = 0;
	v.newstr = ft_strdup("");
	while (str[v.i])
	{
		if (str[v.i] == '$')
			fragment = expand_dollar(str, &v.i, envp, last_status);
		else
			fragment = ft_substr(str, v.i++, 1);
		v.newstr = ft_strjoin_free(v.newstr, fragment);
	}
	free(str);
	return (v.newstr);
}

char	*expand_str(char *str, char **envp, int last_status)
{
	t_expand_view	v;
	char			*fragment;

	v.i = 0;
	v.quote = 0;
	v.newstr = ft_strdup("");
	while (str[v.i])
	{
		if (str[v.i] == '\'' || str[v.i] == '"')
		{
			expand_str_handle_quote(str, &v);
			continue ;
		}
		if (str[v.i] == '$' && v.quote != '\'')
			fragment = expand_dollar(str, &v.i, envp, last_status);
		else
			fragment = ft_substr(str, v.i++, 1);
		v.newstr = ft_strjoin_free(v.newstr, fragment);
	}
	free(str);
	return (v.newstr);
}
