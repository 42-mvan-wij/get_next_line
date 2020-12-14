/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 14:20:46 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/12 14:52:02 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int		lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst *next;

	while (*lst != NULL)
	{
		next = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next;
	}
	return (-1);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_memdup(const void *ptr, size_t size)
{
	void	*dst;

	dst = malloc(size);
	if (dst == NULL)
		return (NULL);
	while (size > 0)
	{
		size--;
		((char *)dst)[size] = ((char *)ptr)[size];
	}
	return (dst);
}

int		put_all_in_line(t_lst *list, char **line, size_t size)
{
	char	*str;

	PRINT("size: %li\n", size);
	*line = malloc(size);
	str = *line;
	if (*line == NULL)
		return (-1);
	while (list != NULL)
	{
		PRINT("adding: <%.*s> (%li)\n", (int)list->size, list->content, list->size);
		ft_memccpy(str, list->content, '\n', list->size);
		str += list->size;
		PRINT("line: <%.*s>\n", (int)size - 1, *line);
		list = list->next;
	}
	(*line)[size - 1] = '\0';
	PRINT("set line: <%s>\n", *line);
	return (1);
}
