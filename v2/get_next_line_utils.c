/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 15:53:48 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/12/05 14:58:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == src)
		return (dst);
	while (n)
	{
		((char *)dst)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
