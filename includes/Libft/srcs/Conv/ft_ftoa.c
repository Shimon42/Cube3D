/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:26:58 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:47:43 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/libft.h"

char	*ft_ftoa(float n, int dec)
{
	int i;
	int neg;
	double temp;
	char *str;
	int strlen;

	strlen = ft_llen((double)n + dec + 2);

	str = ft_calloc(strlen, sizeof(char));
	i = 0;
	neg = 0;
	ft_putnbr((long)n);
	n = n - (long)n;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	ft_putchar('.');
	n *= 10;
	while (i < 10 && i < dec)
	{
		ft_putnbr(n);
		temp = n - (int)n;
		n = (temp * 10);
		i++;
	}

	ft_putstr("\n-------------------------------------------\n");
	return (str);
}