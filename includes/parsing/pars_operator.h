/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_operator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:58:17 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_OPERATOR_H
# define PARS_OPERATOR_H

# include "libft.h"

//liste chaine word/operator 

//liste chaine classic  avec void *content et next
//void *content contient une structure propre au .h

typedef enum e_type
{
	RED_APPEND,
	RED_HEREDOC,
	RED_OUTPUT,
	RED_INPUT,
	PIPE,
	ESPACE,
	WORD,
	INVALID
}	t_type;

typedef struct s_utils_op
{
	t_list	*list_head;
	int		state_node;
	size_t	i_start;
	size_t	i_continue;
	size_t	y;
}	t_utils_op;

t_list	*lst_str_split(char *str);

#endif
