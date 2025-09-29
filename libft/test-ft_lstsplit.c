/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-ft_lstsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:46:47 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/08 12:46:49 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

////#include <stdio.h>
//#include "libft.h"
//
//char *tab[] = {
//	"hello",
//	"world",
//	"foo",
//	"bar",
//	"baz",
//	NULL
//};
//
//t_list *lst_from_tab(char **tab) {
//	t_list	*retval = NULL;
//
//	while (*tab)
//		ft_lstadd_front(&retval, ft_lstnew(*(tab++)));
//	return (retval);
//}
//
//void	print_content(void *str) {
//	printf("%s ", (char *)str);
//}
//
//void	print_list_of_string(void *list) {
//	ft_lstiter(list, print_content);
//	printf("\n-\n");
//}
//
//int	is_foo(t_list *node) {
//	return !ft_strncmp(node->content, "foo", 4);
//}
//int	main() {
//
//	t_list	*list;
//	t_list	*split;
//
//	printf("liste : \n");
//	list = lst_from_tab(tab);
//	ft_lstiter(list, &print_content);
//	printf("\n\n");
//	split = ft_lstsplit(list, &is_foo);
//	printf("liste apres split: \n");
//	ft_lstiter(list, &print_content);
//	printf("\n\n");
//	printf("liste de liste apres split: \n");
//	ft_lstiter(split, &print_list_of_string);
//	return (0);
//}
