/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 16:13:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/17 15:36:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>

void	next(t_buffer **buf)
{
	t_buffer	*next;

	if (*buf == NULL)
		return ;
	next = (*buf)->next;
	if ((*buf)->str == NULL)
		free((*buf)->str);
	free(*buf);
	*buf = next;
}

int		error(t_buffer **buf)
{
	if (buf == NULL)
		return (-1);
	while (*buf != NULL)
		next(buf);
	return (-1);
}

int		has_newline(t_buffer *buf, ssize_t *size)
{
	ssize_t	i;

	i = 0;
	while (i < buf->size && buf->str[i + buf->start] != '\n')
		i++;
	*size += i;
	return (i != buf->size);
}

int		join(t_buffer **buf, char **line, ssize_t size, int end)
{
	ssize_t		i;

	*line = malloc(size + 1);
	if (*line == NULL)
		return (error(buf));
	(*line)[size] = '\0';
	i = 0;
	while ((*buf)->next != NULL)
	{
		ft_memcpy(*line + i, (*buf)->str + (*buf)->start, (*buf)->size);
		i += (*buf)->size;
		next(buf);
	}
	ft_memcpy(*line + i, (*buf)->str + (*buf)->start, size - i);
	if (size - i == (*buf)->size)
		next(buf);
	else
	{
		(*buf)->size -= size - i + 1;
		(*buf)->start += size - i + 1;
	}
	return (end ? 0 : 1);
}

int		get_next_line(int fd, char **line)
{
	static t_buffer	*buf[FD_SETSIZE];
	t_buffer		*cur;
	ssize_t			size;

	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (error(fd < 0 ? NULL : &buf[fd]));
	size = 0;
	if (buf[fd] == NULL)
		buf[fd] = new_buffer(0);
	else if (has_newline(buf[fd], &size))
		return (join(&buf[fd], line, size, 0));
	cur = buf[fd];
	while (cur != NULL)
	{
		cur->next = new_buffer(BUFFER_SIZE);
		cur = cur->next;
		if (cur == NULL)
			return (error(&buf[fd]));
		cur->size = read(fd, cur->str, BUFFER_SIZE);
		if (cur->size < 0)
			return (error(&buf[fd]));
		if (cur->size == 0 || has_newline(cur, &size))
			return (join(&buf[fd], line, size, cur->size == 0));
	}
	return (error(&buf[fd]));
}
