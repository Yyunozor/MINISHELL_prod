/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:15:09 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/24 17:48:02 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_remove(char *str, char *remove)
{
	size_t	i;
	size_t	ret;
	char	quote;

	i = 0;
	ret = 0;
	quote = 0;
	while (str[i])
	{
		if (ft_strchr(remove, str[i]) && quote == 0)
		{
			quote = str[i];
		}
		else if (str[i] == quote)
		{
			quote = 0;
		}
		else
		{
			ret++;
		}
		i++;
	}
	return (ret);
}

static void	remove_quotes_process(char *str, char *newstr, char *remove)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (ft_strchr(remove, str[i]) && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
}

char	*ft_strremove_str(char *str, char *remove)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * (ft_strlen_remove(str, remove) + 1));
	if (newstr == NULL)
		return (NULL);
	remove_quotes_process(str, newstr, remove);
	return (newstr);
}
