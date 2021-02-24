/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 19:11:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/02/24 17:43:36 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	error(t_buffer **buf)
{
	if (buf == NULL)
		return (-1);
	while (*buf != NULL)
		next(buf);
	return (-1);
}

int	error2(int fd, t_buffer **buf_arr)
{
	t_buffer	*buf;

	if (fd < 0)
		return (-1);
	buf = buf_arr[fd];
	while (buf != NULL)
		next(&buf);
	return (-1);
}

void	ft_memcpy(const void *dst, void *src, ssize_t n)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	while (n > 0)
	{
		n--;
		d[n] = s[n];
	}
}

t_buffer	*new_buffer(ssize_t size)
{
	t_buffer	*buf;

	buf = malloc(sizeof(t_buffer));
	if (buf == NULL)
		return (NULL);
	buf->str = malloc(size);
	if (buf->str == NULL)
	{
		free(buf);
		return (NULL);
	}
	buf->size = 0;
	buf->start = 0;
	buf->next = NULL;
	return (buf);
}
