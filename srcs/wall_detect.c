/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wall_detect.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 22:11:09 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/23 20:06:10 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"


t_fpoint to_fpoint(t_point *p)
{
	t_fpoint ret;

	ret.x = p->x;
	ret.y = p->y;
	return (ret);
}

t_point to_point(t_fpoint *p)
{
	t_point ret;

	ret.x = (int)floor(p->x);
	ret.y = (int)floor(p->y);
	return (ret);
}

t_fpoint	closest_grid_h(t_point *p, t_map *m, double angle)
{
	t_fpoint closest;
	
	if (angle > PI && angle < 2 * PI)
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size;
	else
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size  + m->bloc_size;
	if (tan(angle) != 0)
		closest.x = p->x - (p->y - closest.y) / tan(angle);
	if (closest.x < 0)
		closest.x = 0;
	if (closest.y < 0)
		closest.y = 0;
	return (closest);
}

t_fpoint	 closest_grid_v(t_point *p, t_map *m, double angle)
{
	t_fpoint closest;
	
	if (angle > PI / 2.0 && angle < 2 * PI * 0.75)
		closest.x = floor(p->x / m->bloc_size) * m->bloc_size;
	else
		closest.x = floor(p->x / m->bloc_size) * m->bloc_size + m->bloc_size;
	closest.y = p->y - (p->x - closest.x) * tan(angle);
	if (closest.x < 0)
		closest.x = 0;
	if (closest.y < 0)
		closest.y = 0;
	return (closest);
}

t_fpoint closest_wall_h(t_brain *b, t_point *p, double angle)
{
	t_fpoint offset;
	t_fpoint cur_point;
	int is_wall;
	is_wall = 0;

	cur_point = closest_grid_h(p, b->map, angle);
	if (angle > PI && angle < 2 * PI)
	{
		offset.y = -(b->map->bloc_size);
		offset.x = (b->map->bloc_size / tan(angle)) * -1;
	}
	else
	{
		offset.y = b->map->bloc_size;
		offset.x = (b->map->bloc_size / tan(angle)) * 1;
	}
	while (is_wall == 0 && cur_point.x < b->map->px_width && cur_point.x > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x, cur_point.y + 1, 1) == 1 || get_grid(b->map, cur_point.x, cur_point.y - 1, 1) == 1);
		if (is_wall == -1 || is_wall == 1)
			break;
		if (cur_point.x + offset.x < b->map->px_width && cur_point.y + offset.y < b->map->px_height)
		{
			cur_point.x += offset.x;
			cur_point.y += offset.y;
		} else {
			cur_point.x = b->map->px_width;

		 	break;
		}
	}
	return (cur_point);
}

t_fpoint closest_wall_v(t_brain *b, t_point *p, double angle)
{
	t_fpoint cur_point;
	t_fpoint offset;
	int is_wall;

	is_wall = 0;
	cur_point = closest_grid_v(p, b->map, angle);
	if (angle < 2 * PI * 0.75 && angle > PI / 2)
	{
		offset.x = -b->map->bloc_size;
		offset.y = (b->map->bloc_size * tan(angle)) * -1;
	}else{
		offset.x = b->map->bloc_size;
		offset.y = (b->map->bloc_size * tan(angle));
	}
	while (is_wall == 0 && cur_point.y < b->map->px_height && cur_point.y > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x - 1, cur_point.y, 1) == 1 || get_grid(b->map, cur_point.x + 1, cur_point.y, 1) == 1);
		if (is_wall == 1 || is_wall == -1) 
			break;
		if (cur_point.x + offset.x < b->map->px_width && cur_point.y + offset.y < b->map->px_height)
		{
			cur_point.x += offset.x;
			cur_point.y += offset.y;
		} else {
			cur_point.y = b->map->px_height;

		 	break;
		}
	}
	return (cur_point);
}

char		get_wall_side(double angle, int closest)
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

double to_360(double angle)
{
	if (angle < 0)
		return ((2.0 * M_PI) + angle);
	else if (angle > 2*M_PI)
		return (angle - (2.0 * PI));
	return (angle);
}

t_detect	dist_to_wall(t_brain *b, t_point *p, double angle)
{
	t_fpoint closest_h;
	t_fpoint closest_v;
	t_fpoint dists;
	t_detect wall;
	double bad_dist;

	angle = to_360(angle);
	closest_h = closest_wall_h(b, p, angle);
	closest_v = closest_wall_v(b, p, angle);
	dists.x = calc_fdist(to_fpoint(p), closest_h);
	dists.y = calc_fdist(to_fpoint(p), closest_v);
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
	double w_height;
	t_detect wall;
	double dist;
	double cur_col;
	double col_step;
	double cur_angle;

	cur_col = 0;
	col_step = b->player->cam->fov/ c->width;
	c->cur_buff = b->map->frame;
	//printf("START DRAW WALLS\n");
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
		c->color = 0;
		
		c->color = 0x388FBA;
		c->line(new_point(cur_col, 0), new_point(cur_col, c->height/2 - w_height/2 + b->player->z), c);
		
		draw_col(b, w_height,  cur_col, wall);
		
		c->color = 0x91672C;
		//draw_floor(new_point(cur_col, c->height/2 + w_height/2), new_point(cur_col, c->height), c);
		c->line(new_point(cur_col, c->height/2 + w_height/2 + b->player->z), new_point(cur_col, c->height), c);
		cur_col++;
	}
}
/*
void draw_floor(t_brain *b, double w_height, double cur_col, t_detect w)
{
	
}
*/
void draw_col(t_brain *b, double w_height, double cur_col, t_detect w)
{
	int i;
	t_fpoint ratio;
	int color;
	t_buff **texture;
	int texture_col;

	if (w.w_side_hit == 'n' || w.w_side_hit == 's')
		texture_col = (int)w.hit.x % 64;
	else
		texture_col = (int)w.hit.y % 64;
	texture = NULL;
	texture = get_wall_texture(b->map, w.w_side_hit);
	ratio.y = ((*texture)->height / w_height);
	ratio.x = ((*texture)->width / b->map->bloc_size);
	//dprintf(1, "b_size %d - w_height: %f - cur_c %f - ratio %f\n", b->map->bloc_size, w_height, cur_col, ratio);
	i = 0;
	if ((b->ctx->height/2 - w_height/2 + 1) < 0)
		i = ((b->ctx->height/2 - w_height/2 + 1)) * -1;
	if (cur_col == -1)
	{
		dprintf(1, "W_height: %f - ", w_height);
		dprintf(1, "start: %d - ", i);
		dprintf(1, "text_col: %d - ", texture_col);
	}
	i--;
	while (i <= w_height + 1)
	{
		color = pixel_get(*texture, round(texture_col * ratio.x), round(i * ratio.y));

		if ((b->ctx->height/2 - w_height/2 + 1) + i > 0 )
			pixel_put_buff(cur_col, (b->ctx->height/2 - w_height/2 + 1) + i + b->player->z, color, b->map->frame);
		if ((b->ctx->height/2 - w_height/2 + 1) + i > b->ctx->height)
			break;
		i++;
	}
	if (cur_col == -1)
	{
		dprintf(1, "end: %d\n", i);
	}
}