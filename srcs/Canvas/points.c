/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:51:53 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:48:04 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include <math.h>

t_point		new_point(int x, int y)
{
	t_point new;

	new.x = x;
	new.y = y;
	return (new);
}

t_fpoint	new_fpoint(float x, float y)
{
	t_fpoint new;

	new.x = x;
	new.y = y;
	return (new);
}

float		calc_dist(t_fpoint p1, t_fpoint p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));
}
