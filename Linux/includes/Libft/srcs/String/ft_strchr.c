/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:39:54 by shimon            #+#    #+#             */
/*   Updated: 2020/08/03 11:25:47 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == c)
				return ((char*)&s[i]);
			i++;
		}
		if ((s[i] == c && c == '\0'))
			return ((char*)&s[i]);
	}
	return ((char *)NULL);
}
