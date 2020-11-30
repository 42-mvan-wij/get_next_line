/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 15:32:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/30 17:14:04 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 5 // 0?
#endif

int		get_next_line(int fd, char **line)
{
	static char	*test[FD_SETSIZE] = { NULL };
	char		*buf;
	int			read_n;
	size_t		size;
	char		*tmp;

	buf = malloc(BUFFER_SIZE);
	if (test[fd] == NULL)
	{
		*line = malloc(1);
		if (*line == NULL)
			return (-1);
		(*line)[0] = '\0';
	}
	else
		*line = test[fd];
	size = ft_strlen(*line);
	// test[fd];
	while (1)
	{
		read_n = read(fd, buf, BUFFER_SIZE);
		if (read_n == -1)
			return (-1);
		if (read_n == 0)
		{
			free(buf);
			test[fd] = NULL;
			return (0);
		}
		size += read_n;
		tmp = *line;
		*line = malloc(size + 1);
		ft_memcpy(*line, tmp, size - read_n);
		free(tmp);
		tmp = ft_memccpy(*line + size - read_n, buf, '\n', read_n);
		if (tmp != NULL)
		{
			*line[size] = '\0';
			test[fd] = malloc(read_n - (tmp - buf));
			ft_memcpy(test[fd], tmp, read_n - (tmp - buf));
			free(buf);
			return (1);
		}
	}
}
