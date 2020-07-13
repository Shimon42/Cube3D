/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:34:25 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:45:44 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"

void		draw_minimap_closest(t_brain *b, t_fpoint disp, float angle)
{
	int			color;
	t_fpoint	close_h;
	t_fpoint	close_v;
	t_fpoint	p_pos;
	t_detect	wall;

	color = b->ctx->color;
	close_h = closest_grid_h(b->player->pos, b->map, angle);
	close_v = closest_grid_v(b->player->pos, b->map, angle);
	p_pos = map_scaled(b->player->pos, b->map);
	close_h = map_fscaled(&close_h, b->map);
	close_v = map_fscaled(&close_v, b->map);
	wall = dist_to_wall(b, b->player->pos, angle);
	b->ctx->color = color;
	b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
	new_point(disp.x + p_pos.x + (wall.dist * b->map->scale) * cos(angle),
	disp.y + p_pos.y + (wall.dist * b->map->scale) * sin(angle)),
		b->ctx);
	b->ctx->color = 0xFF0000;
	b->ctx->circle(new_fpoint(disp.x + close_h.x, disp.y + close_h.y),
					(b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
	b->ctx->color = 0x00FFFF;
	b->ctx->circle(new_fpoint(disp.x + close_v.x, disp.y + close_v.y),
					(b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
	b->ctx->color = 0x00FFFF;
}

void		draw_minimap_rays(t_brain *b, t_fpoint disp)
{
	t_detect close_h;
	t_detect close_v;

	close_h = closest_wall_h(b, b->player->pos, b->player->angle);
	close_v = closest_wall_v(b, b->player->pos, b->player->angle);
	close_h.hit = map_fscaled(&close_h.hit, b->map);
	close_v.hit = map_fscaled(&close_v.hit, b->map);
	b->ctx->color = 0xFFFF00;
	b->ctx->circle(new_fpoint(disp.x + close_h.hit.x, disp.y + close_h.hit.y),
					(b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
	b->ctx->color = 0xFF00FF;
	b->ctx->circle(new_fpoint(disp.x + close_v.hit.x, disp.y + close_v.hit.y),
					(b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
}

void		draw_fov_map(t_brain *b, t_ctx *c)
{
	t_detect	wall;
	float		dist;
	float		cur_col;
	float		col_step;
	float		cur_angle;

	cur_col = 0;
	col_step = b->player->cam->fov / c->width;
	while (cur_col < c->width)
	{
		cur_angle = b->player->angle - (b->player->cam->fov / 2) +
														(col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		dist = wall.dist;
		b->ctx->color = 0xFF00FF;
		line_on_map(b,
			*b->player->pos,
			new_fpoint(b->player->pos->x + (wall.dist) * cos(cur_angle),
							b->player->pos->y + (wall.dist) * sin(cur_angle)));
		if (cur_col < c->width / 2)
			dist = dist * cos(-(b->player->angle - cur_angle));
		else
			dist = dist * cos((b->player->angle - cur_angle));
		cur_col += c->width / 10;
	}
}
