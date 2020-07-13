/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:07:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:51:31 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	if (s)
	{
		i = 0;
		while (i < n)
			if (((char*)s)[i++] == c)
				return (&((unsigned char *)s)[--i]);
	}
	return (NULL);
}
