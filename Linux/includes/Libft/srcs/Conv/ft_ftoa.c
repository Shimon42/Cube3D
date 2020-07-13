/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:26:58 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:05:35 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_ftoa(float n, int dec)
{
	int			i;
	double		temp;
	char		*str;

	i = ft_llen((double)n + dec + 2);
	str = ft_calloc(i, sizeof(char));
	i = 0;
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
