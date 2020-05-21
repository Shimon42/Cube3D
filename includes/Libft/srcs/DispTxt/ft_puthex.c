/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:42:44 by shimon            #+#    #+#             */
/*   Updated: 2020/05/20 17:53:17 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_puthex(unsigned long n, int upper)
{
	size_t count;

	count = 0;
	if (n < 16)
	{
		if (upper)
			count += ft_putchar("0123456789ABCDEF"[n]);
		else
			count += ft_putchar("0123456789abcdef"[n]);
	}
	else
	{
		count += ft_puthex(n / 16, upper);
		count += ft_puthex(n % 16, upper);
	}
	return (count);
}
