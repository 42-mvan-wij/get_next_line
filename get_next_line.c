/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:49 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/16 17:27:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// temp
#define BUFFER_SIZE 1
#include <stdio.h>

int		get_next_line(int fd, char **line)
{
	static char *start;
	int i;
	char *buf;
	size_t size;
	
	size = 0;
	buf = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		i = 0;
		read(fd, buf, BUFFER_SIZE);
		while (i < BUFFER_SIZE && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			start = buf + i + 1;
	}
	// printf("|%s|\n", *line);
	// *line = malloc(7);
	// read(fd, *line, BUFFER_SIZE);
	// printf("|%s|\n", *line);
	return (-69);
}

int main(void)
{
	char **line;
	get_next_line(0, line);
	return (0);
}