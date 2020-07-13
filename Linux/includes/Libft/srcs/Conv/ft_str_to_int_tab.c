/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_int_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 08:44:13 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:06:40 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		*ft_str_to_int_tab(const char *s1)
{
	int		*dup;
	size_t	length;
	size_t	i;

	i = 0;
	length = 0;
	while (s1 && s1[length] != '\0')
		length++;
	if ((dup = malloc((length + 1) * sizeof(int))) != NULL)
	{
		if (s1)
		{
			if (length == 0)
				length++;
			while (i < length && s1[i] != '\0' && s1)
			{
				dup[i] = s1[i] - '0';
				i++;
			}
		}
		dup[i] = -1;
	}
	return (dup);
}
