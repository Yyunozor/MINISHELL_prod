/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_metacar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:35:42 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/26 10:20:18 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_state_car(char c, int *state_car)
{
	int			i;
	const char	metacar[] = "|<> \t";

	i = 0;
	while (metacar[i])
	{
		if (c == metacar[i])
		{
			*state_car = METACAR;
			return ;
		}
		i++;
	}
	*state_car = ALPHABET;
	return ;
}

void	set_state_quote(char c, int *state_quote)
{
	if (*state_quote == NORMAL)
	{
		if (c == '\'')
			*state_quote = SINGLE;
		else if (c == '"')
			*state_quote = DOUBLE;
	}
	else if (*state_quote == SINGLE)
	{
		if (c == '\'')
			*state_quote = NORMAL;
	}
	else if (*state_quote == DOUBLE)
	{
		if (c == '"')
			*state_quote = NORMAL;
	}
}

int	set_token_struct(char *str, t_token_view *v, t_token **token)
{
	(*token)->str = malloc((sizeof(char))
			* (v->token_end - v->token_start + 1));
	if (!(*token)->str)
		return (1);
	ft_memcpy((*token)->str, str + v->token_start,
		v->token_end - v->token_start);
	(*token)->str[v->token_end - v->token_start] = '\0';
	(*token)->type = v->old_state_car;
	return (0);
}

int	add_node_entry(char *str, t_token_view *v, t_pars_data *data)
{
	t_token	*token;
	t_list	*new_node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (1);
	if (set_token_struct(str, v, &token))
	{
		free(token);
		return (1);
	}
	new_node = ft_lstnew(token);
	if (new_node == NULL)
	{
		free(token);
		free(token->str);
		return (1);
	}
	if (!data->lst_token)
		data->lst_token = new_node;
	else
		ft_lstadd_back(&data->lst_token, new_node);
	return (0);
}

int	pars_metacar(char *str, t_pars_data *data)
{
	t_token_view	v;

	set_state_car(str[0], &v.state_car);
	v.old_state_car = v.state_car;
	v.state_quote = NORMAL;
	v.token_start = 0;
	v.token_end = 0;
	while (str[v.token_end])
	{
		if (v.token_end)
			set_state_quote(str[v.token_end - 1], &v.state_quote);
		set_state_car(str[v.token_end], &v.state_car);
		if (v.state_car != v.old_state_car && v.state_quote == NORMAL)
		{
			if (add_node_entry(str, &v, data))
				return (ft_lstclear(&data->lst_token, del_token), 1);
			v.token_start = v.token_end;
			v.old_state_car = v.state_car;
		}
		v.token_end++;
	}
	if (add_node_entry(str, &v, data))	
		return (ft_lstclear(&data->lst_token, del_token), 1);
	return (0);
}
