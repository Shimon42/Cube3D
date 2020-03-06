/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:11:09 by siferrar          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2020/02/28 11:08:57 by siferrar         ###   ########lyon.fr   */
=======
/*   Updated: 2020/03/06 06:53:55 by siferrar         ###   ########lyon.fr   */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cube3d.h"


t_fpoint to_fpoint(t_fpoint *p)
{
	t_fpoint ret;

	ret.x = p->x;
	ret.y = p->y;
	return (ret);
}

t_fpoint to_point(t_fpoint *p)
{
	t_fpoint ret;

	ret.x = (int)floor(p->x);
	ret.y = (int)floor(p->y);
	return (ret);
}

t_fpoint	closest_grid_h(t_fpoint *p, t_map *m, float angle)
{
	t_fpoint closest;
	
	if (angle > PI && angle < 2 * PI)
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size;
	else
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size  + m->bloc_size;
	closest.x = p->x - (p->y - closest.y) / tan(angle);
	return (closest);
}

t_fpoint	 closest_grid_v(t_fpoint *p, t_map *m, float angle)
{
	t_fpoint closest;
	
	if (angle > PI / 2.0 && angle < 2 * PI * 0.75)
		closest.x = floor(p->x / (float)m->bloc_size) * m->bloc_size;
	else
		closest.x = floor(p->x / (float)m->bloc_size) * m->bloc_size + m->bloc_size;
	closest.y = p->y - (p->x - closest.x) * tan(angle);
	return (closest);
}

t_fpoint closest_wall_h(t_brain *b, t_fpoint *p, float angle)
{
	t_fpoint offset;
	t_fpoint cur_point;
	int is_wall;
	is_wall = 0;

	cur_point = closest_grid_h(p, b->map, angle);
	if (angle > PI && angle < 2 * PI)
	{
		offset.y = -(b->map->bloc_size);
		offset.x = ((float)b->map->bloc_size / tan(angle)) * -1;
	}
	else
	{
		offset.y = b->map->bloc_size;
		offset.x = ((float)b->map->bloc_size / tan(angle)) * 1;
	}
		//dprintf(1, "H :Offset x: %f -  y: %f\n", offset.x, offset.y);
	while (is_wall == 0 && cur_point.x < b->map->px_width && cur_point.x > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x, cur_point.y + 1, 1) == 1 || get_grid(b->map, cur_point.x, cur_point.y - 1, 1) == 1);
		if (is_wall == -1 || is_wall == 1)
			break;
		cur_point.x += offset.x;
		cur_point.y += offset.y;
	}
	return (cur_point);
}

t_fpoint closest_wall_v(t_brain *b, t_fpoint *p, float angle)
{
	t_fpoint cur_point;
	t_fpoint offset;
	int is_wall;

	is_wall = 0;
	cur_point = closest_grid_v(p, b->map, angle);
	if (angle < 2 * PI * 0.75 && angle > PI / 2)
	{
		offset.x = -b->map->bloc_size;
		offset.y = ((float)b->map->bloc_size * tan(angle)) * -1;
	}else{
		offset.x = b->map->bloc_size;
		offset.y = ((float)b->map->bloc_size * tan(angle));
	}
	while (is_wall == 0 && cur_point.y < b->map->px_height && cur_point.y > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x - 1, cur_point.y, 1) == 1 || get_grid(b->map, cur_point.x + 1, cur_point.y, 1) == 1);
		if (is_wall == 1 || is_wall == -1) 
			break;
		cur_point.x += offset.x;
		cur_point.y += offset.y;	
	}
	return (cur_point);
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
	} else
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

float to_360(float angle)
{
	if (angle == 0)
		angle = 0.1;
	if (angle < 0)
		return ((2.0 * M_PI) + angle);
	else if (angle > 2*M_PI)
		return (angle - (2.0 * PI));
	return (angle);
}

t_detect	dist_to_wall(t_brain *b, t_fpoint *p, float angle)
{
	t_fpoint closest_h;
	t_fpoint closest_v;
	t_fpoint dists;
	t_detect wall;
	float bad_dist;

	angle = to_360(angle);
	closest_h = closest_wall_h(b, p, angle);
	closest_v = closest_wall_v(b, p, angle);
	dists.x = calc_dist(*p, closest_h);
	dists.y = calc_dist(*p, closest_v);
	if (dists.x < dists.y)
	{
		bad_dist = dists.x;
		wall.w_side_hit = get_wall_side(angle, 'h');
		wall.from = 'h';
		wall.hit = closest_h;
	}
	else
	{
		bad_dist = dists.y;
		wall.w_side_hit = get_wall_side(angle, 'v');
		wall.from = 'v';
		wall.hit = closest_v;
	}
	wall.dist = bad_dist;
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

void	draw_walls(t_brain *b, t_ctx *c)
{
	float w_height;
	t_detect wall;
	float dist;
	float cur_col;
	float col_step;
	float cur_angle;

	cur_col = 0;
	col_step = b->player->cam->fov/ c->width;
	c->cur_buff = b->map->frame;
	while (cur_col < c->width)
	{
		cur_angle = b->player->angle - (b->player->cam->fov / 2) + (col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		dist = wall.dist;
		if (cur_col < c->width / 2)
			dist = dist * cos(-(b->player->angle - cur_angle));
		else
			dist = dist * cos ((b->player->angle - cur_angle));
		w_height = ((b->map->bloc_size) / dist) * b->player->cam->proj_dist;
		c->color = 0x388FBA;
		if (w_height < b->ctx->height)
			c->line(new_point(cur_col, 0), new_point(cur_col, c->height/2 - w_height/2 + b->player->z), c);
		//draw_sprite(b, b->map->sprites);
		draw_col(b, w_height,  cur_col, wall);
		c->color = 0x91672C;
		if (w_height < b->ctx->height)
			c->line(new_point(cur_col, c->height/2 + w_height/2 + b->player->z - 1), new_point(cur_col, c->height), c);
<<<<<<< Updated upstream
=======
	/*	if (wall.spr_on_path[0] != NULL)
		{
			//dprintf(1, "sprites on ray\n");
			draw_sprite(b, wall.spr_on_path[0], cur_col);
		}*/
>>>>>>> Stashed changes
		cur_col++;
	}
}
/*
void draw_floor(t_brain *b, float w_height, float cur_col, t_detect w)
{
	
}
*/
void draw_col(t_brain *b, float w_height, float cur_col, t_detect w)
{
	int i;
	t_fpoint ratio;
	t_buff **texture;
	int texture_col;
	int mid_wall;

	i = 0;
	mid_wall = (b->ctx->height/2 - w_height/2 + 1);
	texture_col = ((w.w_side_hit == 'n' || w.w_side_hit == 's') ? (int)w.hit.x % 64 : (int)w.hit.y % 64);
	texture = get_wall_texture(b->map, w.w_side_hit);
	ratio.y = ((*texture)->height / w_height);
	ratio.x =  (texture_col + 1) * ((*texture)->width / b->map->bloc_size);
	if (mid_wall < 0)
		i = (mid_wall) * -1;
	while (i <= w_height + 1)
	{
		texture_col = pixel_get(*texture, ratio.x, (i + 1) * ratio.y);
		if (mid_wall + i >= 0)
			pixel_put_buff(cur_col, (b->ctx->height/2 - w_height/2) + i + b->player->z, texture_col, b->map->frame);
		if (mid_wall + i > b->ctx->height)
			break;
		i++;
	}
}