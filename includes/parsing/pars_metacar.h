/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_metacar.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:34:19 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/10 22:12:43 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_METACAR_H
# define PARS_METACAR_H

typedef enum e_typenode
{
	NORMAL,
	SINGLE,
	DOUBLE,
}	t_typenode;

typedef enum e_typecar
{
	NONE,
	METACAR,
	ALPHABET,
}	t_typecar;

typedef struct s_token_view
{
	int		state_car;
	int		old_state_car;
	int		state_quote;
	int		token_start;
	int		token_end;
}	t_token_view;

#endif
