/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putihex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:14:22 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:53:20 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_putihex(unsigned int n, int upper)
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
		count += ft_putihex(n / 16, upper);
		count += ft_putihex(n % 16, upper);
	}
	return (count);
}
