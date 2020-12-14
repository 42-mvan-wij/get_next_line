/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 12:56:38 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/12 14:53:59 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>

static int	check_newline(t_lst **list, t_lst *cur, char **line, size_t size)
{
	char	*char_pos;
	t_lst	*other;

	char_pos = ft_memchr(cur->content, '\n', cur->size);
	if (char_pos == NULL)
		return (0);
	PRINT("encountered newline\n");
	PRINT("size: %li\n", size);
	size += char_pos - cur->content;
	if (put_all_in_line(*list, line, size) == -1)
		return (lstclear(list, free));
	other = malloc(sizeof(t_lst));
	if (other == NULL)
		return (lstclear(list, free));
	other->next = NULL;
	other->size = cur->size - (char_pos - cur->content) - 1;
	PRINT("set size: %li\n", other->size);
	other->content = ft_memdup(char_pos + 1, other->size);
	PRINT("set content: <%.*s>\n", (int)other->size, other->content);
	lstclear(list, free);
	*list = other;
	if (other->content != NULL)
		return (1);
	free(other);
	*list = NULL;
	return (-1);
}

static int	read_part(int fd, t_lst **cur)
{
	(*cur)->next = NULL;
	(*cur)->content = malloc(BUFFER_SIZE);
	if ((*cur)->content == NULL)
		return (0);
	(*cur)->size = read(fd, (*cur)->content, BUFFER_SIZE);
	if ((int)(*cur)->size == -1)
		return (0);
	return (1);
}

static int	advance_or_end(t_lst **list, t_lst **cur, char **line, size_t *size)
{
	int		return_val;

	return_val = check_newline(list, *cur, line, *size);
	if (return_val != 0)
		return (return_val);
	*size += (*cur)->size;
	(*cur)->next = malloc(sizeof(t_lst));
	(*cur) = (*cur)->next;
	if (cur == NULL)
		return (lstclear(list, free));
	return (0);
}

static int	size_cur_init(t_lst **list, t_lst **cur, char **line, size_t *size)
{
	int		return_val;

	*size = 1;
	if (*list == NULL)
	{
		*list = malloc(sizeof(t_lst));
		if (*list == NULL)
			return (-1);
		*cur = *list;
		return (0);
	}
	*cur = *list;
	return_val = advance_or_end(list, cur, line, size);
	if (return_val != 0)
		return (return_val);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_lst	*list[FD_SETSIZE] = { NULL };
	t_lst			*cur;
	size_t			size;
	int				return_val;

	return_val = size_cur_init(&list[fd], &cur, line, &size);
	PRINT("return_val: %i\n", return_val);
	if (return_val != 0)
		return (return_val);
	while (1)
	{
		if (!read_part(fd, &cur))
			return (lstclear(&list[fd], free));
		PRINT("read: <%.*s> (%li)\n", (int)cur->size, cur->content, cur->size);
		if (cur->size == 0)
		{
			PRINT("EOF\n");
			return_val = put_all_in_line(list[fd], line, size);
			lstclear(&list[fd], free);
			return (return_val == -1 ? -1 : 0);
		}
		return_val = advance_or_end(&list[fd], &cur, line, &size);
		if (return_val != 0)
			return (return_val);
	}
}
