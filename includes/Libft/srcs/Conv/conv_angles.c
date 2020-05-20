/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:28:19 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 13:57:43 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/libft.h"

double	ft_inrad(double angle)
{
	return ((angle * PI)/ 180);
}

double	ft_indeg(double angle)
{
	return (angle * 180.0 / PI);
}

float	ft_to_360(float angle)
{
	if (angle == 0)
		angle = 0.1;
	if (angle < 0)
		return ((2.0 * PI) + angle);
	else if (angle > 2 * PI)
		return (angle - (2.0 * PI));
	return (angle);
}