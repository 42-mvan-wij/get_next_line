/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 16:18:18 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/14 20:31:57 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct		s_buffer
{
	char			*str;
	ssize_t			size;
	ssize_t			start;
	struct s_buffer	*next;
}					t_buffer;

int					get_next_line(int fd, char **line);
void				ft_memcpy(const void *dst, void *src, ssize_t n);
t_buffer			*new_buffer(ssize_t size);

#endif
