/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 16:18:18 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/27 14:22:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_buffer
{
	char			*str;
	ssize_t			size;
	ssize_t			start;
	struct s_buffer	*next;
}					t_buffer;

int			get_next_line(int fd, char **line);
void		ft_memcpy(const void *dst, void *src, ssize_t n);
t_buffer	*gnl_new_buffer(ssize_t size);
int			gnl_error(t_buffer **buf_arr);
int			gnl_error_fd(int fd, t_buffer **buf_arr);
void		gnl_next(t_buffer **buf);

#endif
