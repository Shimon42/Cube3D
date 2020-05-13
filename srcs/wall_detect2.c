/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:23:45 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/13 15:24:00 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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

float		to_360(float angle)
{
	if (angle == 0)
		angle = 0.1;
	if (angle < 0)
		return ((2.0 * M_PI) + angle);
	else if (angle > 2 * M_PI)
		return (angle - (2.0 * PI));
	return (angle);
}

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
