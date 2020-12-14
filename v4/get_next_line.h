/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:47 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/12 14:54:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

// # include "../../../libft/libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif
# include <stdio.h>
# define PRINT if(DEBUG+0) printf

typedef struct		s_lst
{
	char			*content;
	size_t			size;
	struct s_lst	*next;
}					t_lst;

int					get_next_line(int fd, char **line);
int					put_all_in_line(t_lst *list, char **line, size_t size);
int					lstclear(t_lst **lst, void (*del)(void *));
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_memdup(const void *ptr, size_t size);

#endif
