/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:11:09 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/22 18:12:32 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_buff		**get_wall_texture(t_map *m, char w_side)
{
	if (w_side == 'n')
		return (&m->w_n);
	if (w_side == 'e')
		return (&m->w_e);
	if (w_side == 's')
		return (&m->w_s);
	if (w_side == 'w')
		return (&m->w_w);
	return (0);
}

char		get_wall_side(float angle, int closest)
{
	if (angle >= 0 & angle < PI)
	{
		if (closest == 'h')
			return ('n');
		if (angle >= 0 && angle < PI / 2.0)
			return ('w');
		else
			return ('e');
	}
	else
	{
		if (closest == 'h')
			return ('s');
		if (angle >= PI && angle < 2.0 * PI * 0.75)
			return ('e');
		else
			return ('w');
	}
	return ('z');
}

void		draw_walls(t_brain *b, t_ctx *c)
{
	float			w_hgt;
	t_detect		wall;
	int				cur_col;
	float			cur_angle;
	int				mid_wall;

	cur_col = 0;
	c->cur_buff = b->map->frame;
	while (cur_col < c->width)
	{
		cur_angle = b->player->divided + (c->col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		b->map->sprites->column[cur_col] = wall.dist;
		wall.dist *= cos((cur_angle < b->player->angle ? -1 : 1)
						* (b->player->angle - cur_angle));
		w_hgt = ((b->map->bloc_size) / wall.dist) * b->player->cam->proj_dist;
		mid_wall = w_hgt / 2;
		if (w_hgt < b->ctx->height)
			draw_sky(b, cur_col, c->divided.y - (float)mid_wall + b->player->z);
		draw_col(b, w_hgt, cur_col, wall);
		if (w_hgt < b->ctx->height)
			draw_floor(b, cur_angle,
				floor(c->divided.y + mid_wall + b->player->z - 1), cur_col);
		cur_col++;
	}
}

void		draw_col(t_brain *b, float w_height, float cur_col, t_detect w)
{
	int			i;
	t_fpoint	ratio;
	t_buff		**texture;
	int			texture_col;
	int			mid_wall;

	mid_wall = (b->ctx->height / 2.0 - w_height / 2.0 + 1);
	texture_col = ((w.w_side_hit == 'n' || w.w_side_hit == 's') ?
	(int)w.hit.x % b->map->bloc_size : (int)w.hit.y % b->map->bloc_size);
	texture = get_wall_texture(b->map, w.w_side_hit);
	ratio.y = ((*texture)->height / w_height);
	ratio.x = (texture_col + 1) * ((*texture)->ratio);
	i = ((mid_wall < 0) ? (mid_wall) * -1 : 0);
	while (i <= w_height + 1)
	{
		texture_col = ((*texture)->is_color != -1 ?
			(*texture)->is_color :
			pixel_get(*texture, ratio.x, (i + 1) * ratio.y));
		if (mid_wall + i + b->player->z >= 0)
			pixel_put(cur_col, mid_wall + i + b->player->z,
													texture_col, b->map->frame);
		if (mid_wall + i > b->ctx->height)
			break ;
		i++;
	}
}
