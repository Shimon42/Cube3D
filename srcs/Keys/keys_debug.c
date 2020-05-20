/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 14:46:34 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 14:55:28 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	disp_keys(t_brain *b)
{
	int i;

	i = 0;
	while (i < 10)
	{
		ft_putnbr(b->keys[i]);
		if (i < 9)
			ft_putstr(", ");
		i++;
	}
	ft_putchar('\n');
}
