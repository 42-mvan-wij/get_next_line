/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 19:11:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/17 15:08:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

void		ft_memcpy(const void *dst, void *src, ssize_t n)
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
