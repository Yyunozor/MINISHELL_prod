/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:20:35 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/25 22:54:22 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	expand_quotes_check(t_token	*token)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'' || token->str[i] == '"')
		{
			if (quote == 0)
				quote = token->str[i];
			else if (token->str[i] == quote)
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (1);
	}
	token->type = WORD;
	return (0);
}

//ne pas remove les quote a linterieur de quote
char	*expand_remove_quote(char *str)
{
	char	*newstr;

	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (str);
	newstr = ft_strremove_str(str, "\'\"");
	if (newstr == NULL)
		return (NULL);
	free(str);
	return (newstr);
}
