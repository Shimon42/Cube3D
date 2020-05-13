/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:11:09 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/13 16:58:46 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_detect	closest_wall_v(t_brain *b, t_fpoint *p, float angle)
{
	t_detect	d;
	t_fpoint	offset;
	int			is_wall;
	int			is_sprite;
	int			verif;

	verif = angle < 2 * PI * 0.75 && angle > PI / 2;
	is_wall = 0;
	d.hit = closest_grid_v(p, b->map, angle);
	d.from = 'v';
	offset.x = b->map->bloc_size * (verif ? -1 : 1);
	offset.y = (b->map->bloc_size * tan(angle)) * (verif ? -1 : 1);
	while (is_wall == 0 && d.hit.y < b->map->px_height && d.hit.y > 0)
	{
		is_wall = (get_grid(b->map, d.hit.x - 1, d.hit.y, 1) == 1 ||
								get_grid(b->map, d.hit.x + 1, d.hit.y, 1) == 1);
		if (is_wall == 1 || is_wall == -1)
			break ;
		d.hit.x += offset.x;
		d.hit.y += offset.y;
	}
	return (d);
}

t_detect	dist_to_wall(t_brain *b, t_fpoint *p, float angle)
{
	t_detect	closest_h;
	t_detect	closest_v;
	t_fpoint	dists;
	t_detect	wall;
	float		bad_dist;

	angle = to_360(angle);
	closest_h = closest_wall_h(b, p, angle);
	closest_v = closest_wall_v(b, p, angle);
	dists.x = calc_dist(*p, closest_h.hit);
	dists.y = calc_dist(*p, closest_v.hit);
	if (dists.x < dists.y)
	{
		bad_dist = dists.x;
		wall.w_side_hit = get_wall_side(angle, 'h');
		wall.hit = closest_h.hit;
	}
	else
	{
		bad_dist = dists.y;
		wall.w_side_hit = get_wall_side(angle, 'v');
		wall.hit = closest_v.hit;
	}
	wall.dist = bad_dist; //corriger fisheye ici
	return (wall);
}

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

void		draw_walls(t_brain *b, t_ctx *c)
{
	float			w_hgt;
	t_detect		wall;
	int				cur_col;
	float			col_step;
	float			cur_angle;
	float			divangle;
	int				mid_wall;
	static t_fpoint	divs = {-420, -420};

	if (divs.x == -420)
	{
		divs.x = c->width / 2;
		divs.y = c->height / 2;
	}
	divangle = b->player->angle - (b->player->cam->fov / 2);
	cur_col = 0;
	col_step = b->player->cam->fov / c->width;
	c->cur_buff = b->map->frame;
	while (cur_col < c->width)
	{
		cur_angle = divangle + (col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		b->map->sprites->column[cur_col] = wall.dist;
		wall.dist *= cos((cur_col < divs.x ? -1 : 1)
									* (b->player->angle - cur_angle)); // voir ligne 151
		w_hgt = ((b->map->bloc_size) / wall.dist) * b->player->cam->proj_dist;
		mid_wall = w_hgt / 2;
		if (w_hgt < b->ctx->height)
			draw_sky(b, b->ctx, cur_col, divs.y - mid_wall + b->player->z);
		draw_col(b, w_hgt, cur_col, wall);
		if (w_hgt < b->ctx->height)
			draw_floor(b, cur_angle,
				floor(divs.y + mid_wall + b->player->z - 1), cur_col);
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

	mid_wall = (b->ctx->height / 2 - w_height / 2 + 1);
	texture_col = ((w.w_side_hit == 'n' || w.w_side_hit == 's') ?
	(int)w.hit.x % b->map->bloc_size : (int)w.hit.y % b->map->bloc_size);
	texture = get_wall_texture(b->map, w.w_side_hit);
	ratio.y = ((*texture)->height / w_height);
	ratio.x = (texture_col + 1) * ((*texture)->ratio);
	i = ((mid_wall < 0) ? (mid_wall) * -1 : 0);
	while (i <= w_height + 1)
	{
		texture_col = pixel_get(*texture, ratio.x, (i + 1) * ratio.y);
		texture_col -= 0x101010;
		if (mid_wall + i >= 0)
			pixel_put(cur_col, mid_wall + i + b->player->z,
													texture_col, b->map->frame);
		if (mid_wall + i > b->ctx->height)
			break ;
		i++;
	}
}
