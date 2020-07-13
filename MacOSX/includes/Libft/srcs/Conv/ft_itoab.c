/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:31:39 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/21 11:40:00 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_checkval(long *value, int base, char *fullbase, char *nbr)
{
	int		sign;
	int		i;

	sign = 1;
	if (*value < 0 && base == 10)
		sign = -1;
	if (*value < 0)
		*value = -*value;
	i = 0;
	if (*value == 0)
		return (-1);
	while (*value > 0)
	{
		nbr[i] = fullbase[*value % base];
		*value = (*value - (*value % base)) / base;
		i++;
	}
	if (sign == -1 && base == 10)
		nbr[i++] = '-';
	return (i);
}

char	*ft_itoab(long value, int base)
{
	char	*nbr;
	char	*fullbase;
	int		i;
	char	temp;

	fullbase = ft_strdup("0123456789ABCDEF");
	nbr = malloc(255 * sizeof(char));
	if (nbr == NULL || base < 2 || base > 16)
		return (NULL);
	if ((i = ft_checkval(&value, base, fullbase, nbr)) == -1)
		return ("0");
	while (value < i / 2)
	{
		temp = nbr[value];
		nbr[value] = nbr[i - value - 1];
		nbr[i - value - 1] = temp;
		value++;
	}
	nbr[i] = '\0';
	return (nbr);
}
