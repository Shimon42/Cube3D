/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:44:05 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:52:25 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char const *s1, char const *s2, int start, int size)
{
	char		*join;
	size_t		i;
	size_t		j;
	size_t		s1len;
	size_t		s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	j = 0;
	if ((size_t)start > s2len)
		start = s2len;
	if ((size_t)size > s2len)
		size = s2len;
	if (!(join = malloc((s1len + size + 1) * sizeof(char))))
		return (NULL);
	while (j < s1len)
		join[i++] = s1[j++];
	j = start;
	while (j < s2len && size--)
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

int		has_eol(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*obj;
	unsigned char	*pobj;

	if ((obj = malloc(count * size)) != NULL)
	{
		pobj = obj;
		while (count--)
			*pobj++ = '\0';
	}
	return (obj);
}

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	if (s)
		while (s[length])
			length++;
	return (length);
}
