/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:47 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/07 16:10:49 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H
 #include <stddef.h>

typedef struct		s_list
{
	char			*content;
	size_t			size;
	struct s_list	*next;
}					t_list;

typedef struct		s_read
{
	char			*content;
	size_t			size;
}					t_read;

// size_t	create(t_list **lst, char *content);
// void	add(t_list *lst, char *content);
// void	collapse(t_list *lst, char *dst);

int					get_next_line(int fd, char **line);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
