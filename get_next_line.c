/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 19:21:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/19 23:56:56 by mvan-wij      ########   odam.nl         */
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
#define PRINT if(DEBUG+0) printf

void	collapse3(t_list *lst, char **dst, size_t size)
{
	int		i;
	char	*str;
	t_list	*next;

	*dst = malloc(size + 1);
	str = *dst;
	while (lst != NULL)
	{
		i = 0;
		while (i < lst->size)
		{
			*str = lst->content[i];
			str++;
			i++;
		}
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
	*str = '\0';
	PRINT("collapsed into: <%s>\n", *dst);
}

char	*ft_strdupn(char *str, int n)
{
	char *dst;

	if (n < 0)
	{
		n = 0;
		while (str[n] != '\0')
			n++;
	}
	dst = malloc(n + 1);
	dst[n] = '\0';
	while (n > 0)
	{
		n--;
		dst[n] = str[n];
	}
	return (dst);
}

int		fn_for_start(char **start, t_list **lst, size_t *size, char **line)
{
	char *s;

	PRINT("processing start: <%s>\n", *start);
	*size = 0;
	s = *start;
	if (s == NULL)
		return (0);
	while (s[*size] != '\0' && s[*size] != '\n')
		(*size)++;
	PRINT("workable start size: %li\n", *size);
	if (s[*size] == '\n')
	{
		*line = ft_strdupn(s, *size);
		if (s[*size + 1] != '\0')
			*start = ft_strdupn(s + *size + 1, -1);
		else
			*start = NULL;
		free(s);
		PRINT("set start: <%s>\n", *start);
		return (1);
	}
	*start = NULL;
	PRINT("set start: <%s>\n", *start);
	(*lst)->content = s;
	(*lst)->size = *size;
	(*lst)->next = malloc(sizeof(t_list));
	*lst = (*lst)->next;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	t_list			*lst;
	t_list			*cur;
	size_t			size;
	int				read_n;
	static char		*start;

	lst = malloc(sizeof(t_list));
	cur = lst;
	if (fn_for_start(&start, &cur, &size, line))
		return (1);
	while (1)
	{
		cur->content = malloc(BUFFER_SIZE);
		cur->next = NULL;
		read_n = read(fd, cur->content, BUFFER_SIZE);
		PRINT("read: <%s> (%i)\n", cur->content, read_n);
		if (read_n == 0)
		{
			// EOF
			cur->size = 0;
			PRINT("found EOF\n");
			collapse3(lst, line, size);
			return (0);
		}
		cur->size = 0;
		while (cur->size < read_n && cur->content[cur->size] != '\n')
			cur->size++;
		size += cur->size;
		PRINT("line size read: %li\n", size);
		if (cur->size < read_n || cur->content[cur->size - 1] == '\n')
		{
			// newline encounter
			PRINT("found newline (%li)\n", cur->size);
			if (cur->size < read_n - 1)
				start = ft_strdupn(cur->content + cur->size + 1, read_n - cur->size);
			PRINT("set start: <%s>\n", start);
			collapse3(lst, line, size);
			return (1);
		}
		cur->next = malloc(sizeof(t_list));
		cur = cur->next;
	}
}

int		main(void)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = get_next_line(0, &line);
		PRINT("\n");
		printf("line: |%s| (%i)\n", line, ret);
		PRINT("\n");
	}
	PRINT("Testing for problems after EOF\n");
	// else printf("\nAfter EOF:\n");
	ret = get_next_line(0, &line); // problem when getting line after last
	PRINT("\n");
	printf("line: |%s| (%i)\n", line, ret);
	ret = get_next_line(0, &line); // problem when getting line after last
	PRINT("\n");
	printf("line: |%s| (%i)\n", line, ret);
	return (0);
}
