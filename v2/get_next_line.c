/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 15:32:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/06 22:46:40 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 5 // 0?
#endif

#ifndef DEBUG
#define DEBUG 0
#endif
#include "stdio.h"
#define PRINT if(DEBUG+0) printf

size_t	fn_for_start2(char **line, char *start)
{
	size_t	size;
	char	*tmp;

	PRINT("start: <%s>\n", start);
	size = 0;
	if (start != NULL)
	{
		while (start[size] != '\n' && start[size] != '\0')
			size++;
	}
	PRINT("size: %li\n", size);
	*line = malloc(size + 1);
	if (*line == NULL && start != NULL)
	{
		free(start);
		start = NULL;
	}
	if (*line == NULL)
		return (-1);
	*line[size] = '\0';
	if (size == 0)
		return (size);
	tmp = start;
	start = malloc(BUFFER_SIZE);
	ft_memccpy(start, tmp + size, '\0', BUFFER_SIZE);
	PRINT("set start: <%s>\n", start);
	ft_memcpy(*line, tmp, size);
	free(tmp);
	PRINT("line: <%.*s>\n", (int)size, *line);
	return (size);
}

size_t	fn_for_start3(char **line, t_read **start)
{
	size_t	size;
	char	*tmp;

	size = 0;
	if (*start == NULL)
	{
		PRINT("start: <%s>\n", tmp=NULL);
		*start = malloc(sizeof(t_read));
		*line = malloc(1);
		if (*line == NULL)
			return (-1);
	}
	else
	{
		PRINT("start: <%.*s> (%i)\n", (int)(*start)->size, (*start)->str, (int)(*start)->size);
		tmp = (*start)->str;
		while (size < (*start)->size && tmp[size] != '\n')
			size++;
		*line = malloc(size + 1);
		if (*line == NULL)
			return (-1);
		ft_memcpy(*line, tmp, size);
		(*start)->str = malloc((*start)->size - size);
		ft_memcpy((*start)->str, tmp + size, (*start)->size - size);
	}
	(*line)[size] = '\0';
	return (size);
}

int		get_next_line2(int fd, char **line)
{
	static char	*test[FD_SETSIZE] = { NULL };
	char		*buf;
	int			read_n;
	size_t		size;
	char		*tmp;

	buf = malloc(BUFFER_SIZE);
	PRINT("buffer malloced\n");
	size = fn_for_start2(line, test[fd]);
	if ((int)size == -1)
	{
		free(buf);
		return (-1);
	}
	PRINT("init line: <%.*s> (%li)\n", (int)size, *line, size);
	while (1)
	{
		read_n = read(fd, buf, BUFFER_SIZE);
		PRINT("read: <%.*s> (%i)\n", read_n, buf, read_n);
		if (read_n == -1)
		{
			free(buf);
			free(*line);
			test[fd] = NULL;
			return (-1);
		}
		if (read_n == 0)
		{
			PRINT("EOF\n");
			free(buf);
			test[fd] = NULL;
			return (0);
		}
		size += read_n;
		PRINT("total size: %li\n", size);
		/** append buffer **/
		PRINT("append start\n");
		tmp = *line;
		*line = malloc(size + 1);
		ft_memcpy(*line, tmp, size - read_n);
		free(tmp);
		tmp = ft_memccpy(*line + size - read_n, buf, '\n', read_n);
		PRINT("append end\n");
		PRINT("line: <%.*s>\n", (int)size, *line);
		/** buffer appended **/
		if (tmp != NULL)
		{
			/** newline found **/
			PRINT("newline\n");
			*(tmp - 1) = '\0';
			PRINT("fixed line: <%s>\n", *line);
			test[fd] = malloc(*line - tmp + size + 1);
			PRINT("test malloced (%li)\n", *line - tmp + size + 1);
			ft_memcpy(test[fd], buf + read_n - *line + tmp - size, *line - tmp + size);
			test[fd][*line - tmp + size] = '\0';
			PRINT("test filled: <%s>\n", test[fd]);
			free(buf);
			return (1);
		}
	}
}

int		get_next_line3(int fd, char **line)
{
	static t_read	*start[FD_SETSIZE] = { NULL };
	int				read_n;
	size_t			size;
	char			*buf;
	char			*tmp;

	size = fn_for_start3(line, &start[fd]);
	buf = malloc(BUFFER_SIZE);
	if (buf == NULL)
		free(buf);
	if ((int)size == -1 || buf == NULL)
		return (-1);
	while (1)
	{
		read_n = read(fd, buf, BUFFER_SIZE);
		PRINT("read: <%.*s> (%i)\n", read_n, buf, read_n);
		if (read_n == -1)
		{
			PRINT("ERROR\n");
			free(buf);
			free(*line);
			free(start[fd]);
			start[fd] = NULL;
			return (-1);
		}
		if (read_n == 0)
		{
			PRINT("EOF\n");
			free(buf);
			free(start[fd]);
			start[fd] = NULL;
			return (0);
		}
		start[fd]->size = 0;
		while (buf[start[fd]->size] != '\n' && (int)start[fd]->size < read_n)
			start[fd]->size++;
		tmp = *line;
		*line = malloc(size + start[fd]->size + 1);
		ft_memcpy(*line, tmp, size);
		ft_memcpy(*line + size, buf, start[fd]->size);
		size += start[fd]->size;
		free(tmp);
		if (buf[start[fd]->size] == '\n')
		{
			PRINT("newline\n");
			(*line)[size] = '\0';
			start[fd]->size = read_n - start[fd]->size - 1;
			start[fd]->str = malloc(start[fd]->size);
			ft_memcpy(start[fd]->str, buf + read_n - start[fd]->size, start[fd]->size);
			free(buf);
			return (1);
		}
	}
}

// int		main(void)
// {
// 	char *line;

// 	get_next_line(0, &line);
// 	printf("line: <%s>\n", line);
// 	get_next_line(0, &line);
// 	printf("line: <%s>\n", line);
// 	get_next_line(0, &line);
// 	printf("line: <%s>\n", line);
// 	return (0);
// }
