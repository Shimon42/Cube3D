/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wall_detect.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 22:11:09 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 17:15:57 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_point	closest_grid_h(t_point *p, t_map *m, double angle)
{
	t_point closest;
	
	if (angle > PI && angle < 2 * PI)
		closest.y = round(p->y / m->bloc_size) * m->bloc_size - 1;
	else
		closest.y = round(p->y / m->bloc_size) * m->bloc_size  + m->bloc_size;
	closest.x = p->x - (p->y - closest.y) / tan(angle);
	if (closest.x < 0)
		closest.x = 0;
	if (closest.y < 0)
		closest.y = 0;
	return (closest);
}

t_point	 closest_grid_v(t_point *p, t_map *m, double angle)
{
	t_point closest;
	
	if (angle > PI / 2.0 && angle < 2 * PI * 0.75)
		closest.x = round(p->x / m->bloc_size) * m->bloc_size - 1;
	else
		closest.x = round(p->x / m->bloc_size) * m->bloc_size + m->bloc_size;
	closest.y = p->y - (p->x - closest.x) * tan(angle);
	if (closest.x < 0)
		closest.x = 0;
	if (closest.y < 0)
		closest.y = 0;
	return (closest);
}

t_point closest_wall_h(t_brain *b, t_point *p, double angle)
{
	t_point offset;
	t_point cur_point;
	int is_wall;
	is_wall = 0;

	cur_point = closest_grid_h(p, b->map, angle);
	if (angle > PI && angle < 2 * PI)
		offset.y = -(b->map->bloc_size);
	else
		offset.y = b->map->bloc_size;
	if (tan(angle) != 0)
		offset.x = (b->map->bloc_size / tan(angle)) * (angle > PI && angle < 2 * PI ? -1 : 1);
	else
		offset.x = 0;
	
	//if (cur_point.x < 0 || cur_point.x > b->map->px_width || cur_point.y < 0 || cur_point.y > b->map->px_height)


	while (is_wall == 0 && cur_point.x < b->map->px_width && cur_point.x > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x, cur_point.y + 1, 1) || get_grid(b->map, cur_point.x, cur_point.y - 1, 1));
		if (is_wall == -1 || is_wall == 1)
			break;
		cur_point.x += offset.x;
		cur_point.y += offset.y;
	}
	return (cur_point);
}

t_point closest_wall_v(t_brain *b, t_point *p, double angle)
{
	t_point cur_point;
	t_point offset;
	int is_wall;

	is_wall = 0;
	cur_point = closest_grid_v(p, b->map, angle);
	if (angle < 2 * PI * 0.75 && angle > PI / 2)
		offset.x = -b->map->bloc_size;
	else
		offset.x = b->map->bloc_size;
	if (tan(angle) != 0)
		offset.y = (b->map->bloc_size * tan(angle)) * (angle < 2 * PI * 0.75 && angle > PI / 2 ? -1 : 1);
	else
		offset.y = b->map->bloc_size;
//	ft_putstr("Cur point (closest grid h):\n");
	//disp_point(&cur_point);
//	ft_putstr("Offset:\n");
//	disp_point(&offset);
	//ft_putint("Angle: ", ft_indeg(angle));
	while (is_wall == 0 && cur_point.y < b->map->px_height && cur_point.y > 0)
	{
		is_wall = (get_grid(b->map, cur_point.x - 1, cur_point.y, 1) || get_grid(b->map, cur_point.x + 1, cur_point.y, 1));
		if (is_wall == 1 || is_wall == -1) 
			break;
		cur_point.x += offset.x;
		cur_point.y += offset.y;
	}
	return (cur_point);
}

char		get_wall_side(double angle, int closest)
{
	if (angle >= 0 & angle < PI)
	{
		if (closest == 'h')
			return ('n');
		if (angle >= 0 && angle < PI / 2)
			return ('w');
		else
			return ('e');
	} else
	{
		if (closest == 'h')
			return ('s');
		if (angle >= PI && angle < 2 * PI * 0.75)
			return ('e');
		else
			return ('w');
	}
	return ('z');
}

t_detect	dist_to_wall(t_brain *b, t_point *p, double angle)
{
	t_point closest_h;
	t_point closest_v;
	t_point dists;
	t_detect wall;
	double bad_dist;

	closest_h = closest_wall_h(b, p, angle);
	closest_v = closest_wall_v(b, p, angle);
	dists.x = calc_dist(*p, closest_h);
	dists.y = calc_dist(*p, closest_v);
	if (dists.x < dists.y)
	{
		bad_dist = dists.x;
		wall.w_side_hit = get_wall_side(angle, 'h');
	}
	else
	{
		bad_dist = dists.y;
		wall.w_side_hit = get_wall_side(angle, 'v');
	}

	wall.dist = bad_dist;
//	dprintf(1, "HIT: %c\n", wall.w_side_hit);
	
	return (wall);
}

int		get_wall_color(t_map *m, char w_side)
{
	if (w_side == 'n')
		return (m->w_n);
	if (w_side == 'e')
		return (m->w_e);
	if (w_side == 's')
		return (m->w_s);
	if (w_side == 'w')
		return (m->w_w);
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
	//printf("START DRAW WALLS\n");
	while (cur_col < c->width)
	{
		cur_angle = b->player->angle - (b->player->cam->fov / 2) + (col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		dist = wall.dist;
		if (cur_col < c->width / 2)
			dist = dist * cos (b->player->cam->fov/2);
		else
			dist = dist * cos (-(b->player->cam->fov/2));
		w_height = ((b->map->bloc_size) / dist) * b->player->cam->proj_dist;
		//dprintf(1, "Wall Height: %f\n", w_height);
		c->color = 0;
		if (w_height < c->height)
		{
			c->color = 0x388FBA;
			c->line(new_point(cur_col, 0), new_point(cur_col, c->height/2 - w_height/2), c);
			
			c->color = get_wall_color(b->map, wall.w_side_hit);
			c->line(new_point(cur_col, c->height/2 - w_height/2), new_point(cur_col, c->height/2 + w_height/2), c);
			
			c->color = 0x91672C;
			c->line(new_point(cur_col, c->height/2 + w_height/2), new_point(cur_col, c->height), c);
		
		}else{
			c->color = get_wall_color(b->map, wall.w_side_hit);
			c->line(new_point(cur_col, 0), new_point(cur_col, c->height), c);
		}
		cur_col++;
	}
}


