/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:29:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:26:48 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
