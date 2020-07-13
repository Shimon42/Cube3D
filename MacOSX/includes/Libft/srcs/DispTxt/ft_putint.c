/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:21:52 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:28:06 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putint(char *name, int nbr)
{
	ft_putstr(name);
	ft_putchar(' ');
	ft_putnbr(nbr);
	ft_putchar('\n');
}
