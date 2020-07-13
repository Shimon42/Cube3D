/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:43:55 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:51:44 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	unsigned const char	*psrc;
	size_t				i;

	i = 0;
	pdst = (unsigned char*)dst;
	psrc = (unsigned char*)src;
	if (psrc && pdst)
	{
		if (psrc < pdst)
			while (++i <= len)
				pdst[len - i] = psrc[len - i];
		else
			while (len-- > 0)
				*(pdst++) = *(psrc++);
	}
	else
		return (ft_memcpy(pdst, psrc, len));
	return (dst);
}
