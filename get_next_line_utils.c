/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:48 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/19 14:31:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

size_t	create(t_list **lst, char *content)
{
	size_t	len;

	*lst = malloc(sizeof(t_list));
	len = 0;
	if (content != NULL)
	{
		(*lst)->content = content;
		while (content[len] != '\0')
			len++;
	}
	else
	{
		(*lst)->content = malloc(1);
		(*lst)->content[0] = '\0';
	}
	(*lst)->next = NULL;
	return (len);
}

void	add(t_list *lst, char *content)
{
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_list));
	lst->next->content = content;
	lst->next->next = NULL;
}

void	collapse(t_list *lst, char *dst)
{
	int		i;
	t_list	*tmp;

	while (lst != NULL)
	{
		printf("new part\n");
		i = 0;
		while (lst->content[i] != '\0')
		{
			*dst = lst->content[i];
			dst++;
			i++;
		}
		printf("part added\n");
		tmp = lst->next;
		free(lst->content);
		free(lst);
		printf("part freed\n");
		lst = tmp;
	}
}
