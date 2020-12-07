/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:47 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/05 16:42:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct		s_read
{
	char			*str;
	size_t			size;
}					t_read;

void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
size_t				ft_strlen(const char *s);
int					get_next_line(int fd, char **line);

#endif
