/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:36:56 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/28 03:37:38 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	del_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	free(token->str);
	free(token);
}

void	del_token2(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	free(token);
}

void	del_lst_token(void *token_lst)
{
	t_list	*tmp;

	tmp = token_lst;
	ft_lstclear(&tmp, del_token);
}

void	del_lst_scmd(void *ptr)
{
	size_t	i;
	t_scmd	*scmd;

	i = 0;
	scmd = (t_scmd *)ptr;
	while (i < scmd->nbr_of_argv)
	{
		free(scmd->argv[i]);
		i++;
	}
	free(scmd->argv);
	free(scmd->red);
	free(scmd);
}

/*
 * clear_simple_cmd_mixed:
 * Each node in data->lst_simple_cmd initially holds a token sub-list in
 * node->lst. After successful scmd conversion we replace node->content with
 * the t_scmd* and we free ONLY the token structs (without their strings) via
 * del_token2 so that the argv/redirect parsing can re-use the strings.
 * On an error occurring mid-conversion, the list becomes "mixed": earlier
 * nodes hold scmd*, later nodes still hold token sub-lists. A plain
 * ft_lstclear(&list, del_lst_token) would attempt to interpret scmd* as a
 * t_list* head and double free or segfault. This function walks the list and
 * frees appropriately based on whether node->lst looks like a valid token
 * list (non NULL and its first element's token pointer seems plausible) or a
 * constructed scmd (node->lst was NULLed after conversion).
 */
void	clear_simple_cmd_mixed(t_list **lst)
{
	t_list *cur;
	t_list *next;

	cur = *lst;
	while (cur)
	{
		next = cur->next;
		if (cur->is_scmd)
			del_lst_scmd(cur->scmd);
		else
			ft_lstclear(&cur->lst, del_token);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
//
//void	print_lst_scmd(t_list *lst)
//{
//	while (lst)
//	{
//		size_t i = 0;
//		while (i < 2)
//		{	
//			printf("argv[%ld] : %s\n", i, lst->scmd->argv[i]);
//			i++;
//		}
//		printf("command path : %s\n", lst->scmd->command_path);
//		printf("nbr_of_red : %ld\n", lst->scmd->nbr_of_red);
//		i = 0;
//		while (i < lst->scmd->nbr_of_red)
//		{
//			printf("redir type : %d, word : %s\n", lst->scmd->red[i].type,
//				lst->scmd->red[i].word);
//			i++;
//		}
//		lst = lst->next;
//	}
//}
//
//void	print_lst(t_list *lst)
//{
//	int	i;
//
//	i = 0;
//	while (lst)
//	{
//		printf("%d: -%s- ", i, (char *)lst->token->str);
//		if (lst->token->type == RED_APPEND)
//			printf("redir append");
//		else if (lst->token->type == RED_HEREDOC)
//			printf("redir heredoc");
//		else if (lst->token->type == RED_OUTPUT)
//			printf("redir output");
//		else if (lst->token->type == RED_INPUT)
//			printf("redir input");
//		else if (lst->token->type == PIPE)
//			printf("pipe");
//		else if (lst->token->type == ESPACE)
//			printf("space");
//		else if (lst->token->type == WORD)
//			printf("word");
//		printf("\n");
//		lst = lst->next;
//		i++;
//	}
//}
//
//void	print_lst_double(t_list *lst)
//{
//	while (lst)
//	{
//		print_lst(lst->lst);
//		printf("-\n");
//		lst = lst->next;
//	}
//}
