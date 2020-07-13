/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:32:31 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:26:27 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	length;
	size_t	i;

	i = 0;
	length = 0;
	while (s1 && s1[length] != '\0')
		length++;
	if ((dup = malloc((length + 1) * sizeof(char))) != NULL)
	{
		if (s1)
		{
			if (length == 0)
				length++;
			while (i < length && s1[i] != '\0' && s1)
			{
				dup[i] = s1[i];
				i++;
			}
		}
		dup[i] = '\0';
	}
	return (dup);
}
