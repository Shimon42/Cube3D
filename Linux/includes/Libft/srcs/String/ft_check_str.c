/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:02:28 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/22 15:04:37 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_check_str(char *str, char *chrs)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		while (chrs[i])
		{
			if (*str == chrs[i])
				flag = 1;
			i++;
		}
		if (flag == 0)
			return (str);
		flag = 0;
		i = 0;
		str++;
	}
	return (NULL);
}
