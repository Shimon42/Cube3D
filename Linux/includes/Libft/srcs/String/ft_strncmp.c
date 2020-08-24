/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:29:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/24 12:57:51 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const char *ps1;
	const char *ps2;

	ps1 = s1;
	ps2 = s2;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (*ps1 && *ps2)
		if ((unsigned char)*ps1++ != (unsigned char)*ps2++
			|| !(*ps1 || *ps2))
			return ((unsigned char)*--ps1 - (unsigned char)*--ps2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char *ps1;
	const char *ps2;

	ps1 = s1;
	ps2 = s2;
	if (n > 0)
		while (n--)
			if ((unsigned char)*ps1++ != (unsigned char)*ps2++
				|| !(*ps1 || *ps2))
				return ((unsigned char)*--ps1 - (unsigned char)*--ps2);
	return (0);
}
