/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:51:40 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/20 13:58:26 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_fpoint	closest_grid_h(t_fpoint *p, t_map *m, float angle)
{
	t_fpoint	closest;

	if (angle > PI && angle < 2 * PI)
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size;
	else
		closest.y = floor(p->y / m->bloc_size) * m->bloc_size + m->bloc_size;
	closest.x = p->x - (p->y - closest.y) / tan(angle);
	return (closest);
}

t_fpoint	closest_grid_v(t_fpoint *p, t_map *m, float angle)
{
	t_fpoint	closest;

	if (angle > PI / 2.0 && angle < 2 * PI * 0.75)
		closest.x = floor(p->x / (float)m->bloc_size) * m->bloc_size;
	else
		closest.x = floor(p->x / (float)m->bloc_size) *
												m->bloc_size + m->bloc_size;
	closest.y = p->y - (p->x - closest.x) * tan(angle);
	return (closest);
}

t_detect	closest_wall_h(t_brain *b, t_fpoint *p, float angle)
{
	t_fpoint	offset;
	t_detect	d;
	int			is_wall;
	int			is_sprite;
	int			verif;

	verif = angle > PI && angle < 2 * PI;
	is_wall = 0;
	d.hit = closest_grid_h(p, b->map, angle);
	d.from = 'h';
	offset.y = (b->map->bloc_size) * (verif ? -1 : 1);
	offset.x = ((float)b->map->bloc_size / tan(angle)) * (verif ? -1 : 1);
	while (is_wall == 0 && d.hit.x < b->map->px_width && d.hit.x > 0)
	{
		is_wall = (get_grid(b->map, d.hit.x, d.hit.y + 1, 1) == 1 ||
								get_grid(b->map, d.hit.x, d.hit.y - 1, 1) == 1);
		if (is_wall == -1 || is_wall == 1)
			break ;
		d.hit.x += offset.x;
		d.hit.y += offset.y;
	}
	return (d);
}

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

	angle = ft_to_360(angle);
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
	wall.dist = bad_dist;
	return (wall);
}
