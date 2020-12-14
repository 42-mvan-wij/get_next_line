/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 19:21:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/11 12:55:50 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

// tmp
#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 5 // 0?
#endif
#include <stdio.h>
#ifndef DEBUG
 #define DEBUG 0
#endif
// #define PRINT if(DEBUG+0) printf

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <sys/select.h>

// void	collapse3_old(t_list *lst, char **dst, size_t size)
// {
// 	size_t	i;
// 	char	*str;
// 	t_list	*next;

// 	*dst = malloc(size + 1);
// 	str = *dst;
// 	while (lst != NULL)
// 	{
// 		i = 0;
// 		while (i < lst->size)
// 		{
// 			*str = lst->content[i];
// 			str++;
// 			i++;
// 		}
// 		next = lst->next;
// 		free(lst->content);
// 		free(lst);
// 		lst = next;
// 	}
// 	*str = '\0';
// // (.*)PRINT("collapsed into: <%s>\n", *dst);
// }

// char	*ft_strdupn(char *str, int n)
// {
// 	char *dst;

// 	if (n < 0)
// 	{
// 		n = 0;
// 		while (str[n] != '\0')
// 			n++;
// 	}
// 	dst = malloc(n + 1);
// 	dst[n] = '\0';
// 	while (n > 0)
// 	{
// 		n--;
// 		dst[n] = str[n];
// 	}
// 	return (dst);
// }

// int		fn_for_start2_old(t_read *start, t_list **lst, size_t *size, char **line)
// {
// 	char	*s;

// // (.*)PRINT("processing start: <%.*s> (%li) [%s]\n", start->size, start->content, start->size, start->content);
// 	*size = 0;
// 	s = start->content;
// 	if (s == NULL)
// 		return (0);
// 	while (*size < start->size && s[*size] != '\n')
// 		(*size)++;
// // (.*)PRINT("workable start size: %li\n", *size);
// 	if (s[*size] == '\n')
// 	{
// 		*line = ft_strdupn(s, *size);
// 		start->content = NULL;
// 		if (*size < start->size)
// 			start->content = ft_strdupn(s + *size + 1, start->size - *size - 1);
// 		start->size = *size < start->size ? start->size - *size - 1 : 0;
// 		free(s);
// // (.*)PRINT("set start: <%.*s> (%li) [%s]\n", start->size, start->content, start->size, start->content);
// 		return (1);
// 	}
// 	start->content = NULL;
// 	start->size = 0;
// // (.*)PRINT("set start: <%.*s> (%li) [%s]\n", start->size, start->content, start->size, start->content);
// 	(*lst)->content = s;
// 	(*lst)->size = *size;
// 	(*lst)->next = malloc(sizeof(t_list));
// 	*lst = (*lst)->next;
// 	return (0);
// }

// int		fn_for_start_old(char **start, t_list **lst, size_t *size, char **line)
// {
// 	char *s;

// // (.*)PRINT("processing start: <%s>\n", *start);
// 	*size = 0;
// 	s = *start;
// 	if (s == NULL)
// 		return (0);
// 	while (s[*size] != '\0' && s[*size] != '\n')
// 		(*size)++;
// // (.*)PRINT("workable start size: %li\n", *size);
// 	if (s[*size] == '\n')
// 	{
// 		*line = ft_strdupn(s, *size);
// 		if (s[*size + 1] != '\0')
// 			*start = ft_strdupn(s + *size + 1, -1);
// 		else
// 			*start = NULL;
// 		free(s);
// // (.*)PRINT("set start: <%s>\n", *start);
// 		return (1);
// 	}
// 	*start = NULL;
// // (.*)PRINT("set start: <%s>\n", *start);
// 	(*lst)->content = s;
// 	(*lst)->size = *size;
// 	(*lst)->next = malloc(sizeof(t_list));
// 	*lst = (*lst)->next;
// 	return (0);
// }

// int		get_next_line_old(int fd, char **line)
// {
// 	t_list			*lst;
// 	t_list			*cur;
// 	size_t			size;
// 	size_t			read_n;
// 	static t_read	start;

// 	lst = malloc(sizeof(t_list));
// 	cur = lst;
// 	if (fn_for_start2_old(&start, &cur, &size, line))
// 		return (1);
// 	while (1)
// 	{
// 		cur->content = malloc(BUFFER_SIZE);
// 		cur->next = NULL;
// 		read_n = read(fd, cur->content, BUFFER_SIZE);
// 		if ((int)read_n == -1)
// 			return (-1); // possibly more freeing to do
// // (.*)PRINT("read: <%.*s> (%i)\n", read_n, cur->content, read_n);
// 		if (read_n == 0)
// 		{
// 			// EOF
// 			cur->size = 0;
// // (.*)PRINT("found EOF\n");
// 			collapse3_old(lst, line, size);
// 			return (0);
// 		}
// 		cur->size = 0;
// 		while (cur->size < read_n && cur->content[cur->size] != '\n')
// 			cur->size++;
// 		size += cur->size;
// // (.*)PRINT("line size read: %li\n", size);
// 		if (cur->size < read_n || cur->content[cur->size - 1] == '\n')
// 		{
// 			// newline encounter
// // (.*)PRINT("found newline (%li)\n", cur->size);
// 			if (cur->size < read_n - 1)
// 			{
// 				start.size = read_n - cur->size - 1;
// 				start.content = ft_strdupn(cur->content + cur->size + 1, start.size);
// 			}
// // (.*)PRINT("set start: <%.*s> (%li) [%s]\n", start.size, start.content, start.size, start.content);
// 			collapse3_old(lst, line, size);
// 			return (1);
// 		}
// 		cur->next = malloc(sizeof(t_list));
// 		cur = cur->next;
// 	}
// }

int	collapse(t_list *lst, char **dst, size_t size)
{
	size_t		i;
	t_list	*next;
	char	*str;

	*dst = malloc(size + 1);
	if (*dst == NULL)
		return (-1); // free?
	str = *dst;
	while (lst != NULL)
	{
		i = 0;
		while (i < lst->size && i < size)
		{
			*str = lst->content[i];
			str++;
			i++;
		}
		next = lst->next;
		if (next == NULL && size < lst->size)
		{
			lst->size -= size + 1;
			ft_memcpy(lst->content, lst->content + size + 1, lst->size);
			// printf("set start: <%.*s> (%li)\n", (int)lst->size, lst->content, lst->size);
		}
		else
		{
			size -= lst->size;
			// printf("content: %p\n", lst->content);
			// printf("list: %p\n", lst);
			// free(lst->content);
			// free(lst);
		}
		lst = next;
	}
	*str = '\0';
	return (0);
}

int		fn_for_start(t_list **lst, char **dst)
{
	size_t i;

	if (*lst == NULL)
		return (0);
	// printf("start: <%.*s> (%li)\n", (int)(*lst)->size, (*lst)->content, (*lst)->size);
	i = 0;
	while ((*lst)->content[i] != '\n' && i < (*lst)->size)
		i++;
	// printf("i: %li\n", i);
	if (i < (*lst)->size && (*lst)->content[i] == '\n')
	{
		*dst = malloc(i + 1);
		if (*dst == NULL)
			return (-1); // not handled properly (free?)
		ft_memcpy(*dst, (*lst)->content, i);
		(*dst)[i] = '\0';
		(*lst)->size -= i + 1;
		ft_memcpy((*lst)->content, (*lst)->content + i + 1, (*lst)->size);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*lst[FD_SETSIZE] = { NULL };
	t_list			*cur;
	size_t			tmp;
	size_t			size;

	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	if (fn_for_start(&lst[fd], line))
		return (1);
	cur = malloc(sizeof(t_list));
	if (cur == NULL)
		return (-1); // free?
	size = 0;
	if (lst[fd] == NULL)
		lst[fd] = cur;
	else
	{
		lst[fd]->next = cur;
		size = lst[fd]->size;
	}
	while (1)
	{
		cur->next = NULL;
		cur->content = malloc(BUFFER_SIZE);
		if (cur->content == NULL)
			return (-1); // free?
		cur->size = read(fd, cur->content, BUFFER_SIZE);
		// printf("read: <%.*s> (%li)\n", (int)cur->size, cur->content, cur->size);
		if ((int)cur->size == -1)
		{
			return (-1); // free?
		}
		if (cur->size == 0)
		{
			if (collapse(lst[fd], line, size) == -1)
				return (-1); // free?
			lst[fd] = NULL;
			return (0);
		}
		tmp = 0;
		while (tmp < cur->size && cur->content[tmp] != '\n')
			tmp++;
		size += tmp;
		if (cur->content[tmp] == '\n')
		{
			if (collapse(lst[fd], line, size) == -1)
				return (-1); // free?
			lst[fd] = cur;
			return (1);
		}
		cur->next = malloc(sizeof(t_list));
		if (cur->next == NULL)
			return (-1); // free?
		cur = cur->next;
	}
}

// int main2(){
// 	char *line;
// 	int ret;
// 	ret = 1;
// 	while (ret == 1)
// 	{
// 		ret = get_next_line(0, &line);
// 		printf("<%s> [%i]\n", line, ret);
// 	}
// 	printf("-----\n");
// 	ret = get_next_line(0, &line);
// 	printf("<%s> [%i]\n", line, ret);
// 	ret = get_next_line(0, &line);
// 	printf("<%s> [%i]\n", line, ret);
// 	ret = get_next_line(0, &line);
// 	printf("<%s> [%i]\n", line, ret);
// 	ret = get_next_line(0, &line);
// 	printf("<%s> [%i]\n", line, ret);
// 	ret = get_next_line(0, &line);
// 	printf("<%s> [%i]\n", line, ret);
// 	return (0);
// }