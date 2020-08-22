/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:31:18 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/17 15:56:46 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	draw_floor(t_brain *b,
				double cur_angle, int w_start, double col)
{
	t_fpoint	div;
	t_fpoint	cossin;
	t_point		pos;
	float		dist;
	int			color;

	cossin.x = cos(cur_angle);
	cossin.y = sin(cur_angle);
	div.x = (double)b->map->bloc_size / 2;
	div.y = b->player->cam->proj_size.y / 2;
	while (w_start < b->ctx->height)
	{
		dist = ((div.x) / ((w_start - (int)floor(b->player->z)) -
										(div.y))) * b->player->cam->proj_dist;
		pos.x = (int)(dist * cossin.x + b->player->pos->x);
		pos.y = (int)(dist * cossin.y + b->player->pos->y);
		color = (b->map->floor->is_color != -1 ?
			b->map->floor->is_color :
			pixel_get(b->map->floor, pos.x % b->map->floor->width,
							pos.y % b->map->floor->height));
		pixel_put(col, w_start, color, b->map->frame);
		w_start++;
	}
}
