/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:49 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/19 17:53:44 by mvan-wij      ########   odam.nl         */
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

void	collapse2(t_list *lst, char **dst, size_t size)
{
	int		i;
	char	*str;
	t_list	*next;
	int		tmp;

	tmp = 0;
	PRINT("will malloc\n");
	*dst = malloc(size + 1);
	PRINT("mallocced\n");
	str = *dst;
	while (lst != NULL)
	{
		PRINT("while 1\n");
		i = 0;
		PRINT("inbtwn\n");
		while (lst->content[i] != '\0')
		{
			PRINT("%i ", tmp++);
			PRINT("char\n");
			*str = lst->content[i];
			str++;
			i++;
		}
		PRINT("after while 2\n");
		next = lst->next;
		PRINT("will free\n");
		free(lst->content);
		free(lst);
		PRINT("freed\n");
		lst = next;
		PRINT("next\n");
	}
	*str = '\0';
}

char	*ft_strdup(char *str)
{
	char	*duped;
	int		len;

	PRINT("duping |%s|\n", str);
	len = 0;
	while (str[len] != '\0')
		len++;
	duped = malloc(len + 1);
	PRINT("dupe mallocced\n");
	duped[len] = '\0';
	while (len > 0)
	{
		len--;
		duped[len] = str[len];
	}
	PRINT("duped: |%s|\n", duped);
	return (duped);
}

int		function_for_start(char **start, t_list **lst, size_t *size, char **line)
{
	char	*s;
	char	c;

	s = *start;
	PRINT("checking start: |%s|\n", s);
	*size = 0;
	if (s == NULL)
		return (0);
	while (s[*size] != '\0' && s[*size] != '\n')
		(*size)++;
	PRINT("set size: %lu\n", *size);
	if (s[*size] == '\n' || *size == 0)
	{
		PRINT("newline in start\n");
		c = s[*size];
		s[*size] = '\0';
		PRINT("duping into line\n");
		*line = ft_strdup(s);
		PRINT("relocating start\n");
		if (c == '\n' && s[*size + 1] != '\0')
			*start = ft_strdup(s + *size + 1);
		// if (*size != 0)
		else
			*start = NULL;
		PRINT("relocated start: |%s| (%p -> %p)\n", *start, s, *start);
		free(s);
		PRINT("freed old start\n");
		return (1);
	}
	*start = NULL;
	PRINT("adding to list\n");
	(*lst)->content = s;
	(*lst)->next = malloc(sizeof(t_list));
	*lst = (*lst)->next;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	size_t		size;
	t_list		*lst;
	t_list		*current;
	int			read_v;
	int			i;
	static char	*start;

	lst = malloc(sizeof(t_list));
	current = lst;
	if (function_for_start(&start, &current, &size, line))
		return (1);
	while (1)
	{
		current->content = malloc(BUFFER_SIZE + 1);
		current->next = NULL;
		read_v = read(fd, current->content, BUFFER_SIZE);
		current->content[read_v] = '\0';
		PRINT("read: |%s|\n", current->content);
		if (read_v == 0)
		{
			PRINT("found EOF\n");
			// start = NULL;
			PRINT("will collapse\n");
			PRINT("size: %lu\n", size);
			collapse2(lst, line, size);
			PRINT("has collapsed\n");
			return (0);
		}
		i = 0;
		while (i <= read_v && current->content[i] != '\n')
			i++;
		if (i <= read_v)
		{
			PRINT("found newline\n");
			current->content[i] = '\0';
			start = ft_strdup(current->content + i + 1);
			PRINT("set start: |%s|\n", start);
			PRINT("will collapse\n");
			PRINT("size: %lu\n", size + i);
			collapse2(lst, line, size + i);
			PRINT("has collapsed\n");
			return (1);
		}
		size += read_v;
		current->next = malloc(sizeof(t_list));
		current = current->next;
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
	else printf("\nAfter EOF:\n");
	ret = get_next_line(0, &line); // problem when getting line after last
	PRINT("\n");
	printf("line: |%s| (%i)\n", line, ret);
	ret = get_next_line(0, &line); // problem when getting line after last
	PRINT("\n");
	printf("line: |%s| (%i)\n", line, ret);
	return (0);
}
