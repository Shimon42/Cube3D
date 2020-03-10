/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:31:18 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/10 17:42:43 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void draw_floor(t_brain *b, t_ctx *c,
				double cur_angle, int w_start, double col)
{
	t_fpoint div;
	t_fpoint cossin;
	t_point pos;
	double dist;
	int color;

	cossin.x = cos(cur_angle);
	cossin.y = sin(cur_angle);
	div.x = (double)b->map->bloc_size/2;
	div.y = b->player->cam->proj_size.y/2;
	while (w_start < b->ctx->height)
	{
		dist = ((div.x) / (w_start - (div.y))) * b->player->cam->proj_dist;
		pos.x = (int)(dist * cossin.x + b->player->pos->x);
		pos.y = (int)(dist * cossin.y + b->player->pos->y);
		color = pixel_get(b->map->floor, pos.x % b->map->floor->width,
							pos.y % b->map->floor->height);
		pixel_put_buff(col, w_start, color, b->map->frame);
		w_start++;
	}
}