/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wall_detect.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 22:11:09 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 17:59:15 by siferrar    ###    #+. /#+    ###.fr     */
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
	return (closest);
}

t_point closest_wall_h(t_brain *b, t_point *p, double angle)
{
	t_point offset;
	t_point cur_point;
	int wall;
	wall = 0;

	cur_point = closest_grid_h(p, b->map, angle);
	if (angle > PI && angle < 2 * PI)
		offset.y = -b->map->bloc_size;
	else
		offset.y = b->map->bloc_size;
	offset.x = (b->map->bloc_size / tan(angle));
	disp_point(&offset);
	ft_putstr("Cur point");
	disp_point(&cur_point);
	while (wall == 0 && cur_point.x < b->map->px_width && cur_point.x > 0)
	{
		if (get_grid(b->map, cur_point.x, cur_point.y, 1) == 1)
			wall = 1;
		cur_point.x += offset.x;
		cur_point.y += offset.y;
	}
	return (cur_point);
}

t_point closest_wall_v(t_brain *b, t_point *p, double angle)
{
	t_point cur_point;
	t_point offset;
	int wall;

	wall = 0;
	cur_point = closest_grid_v(p, b->map, angle);
	if (angle < 2 * PI * 0.75 && angle > PI / 2)
		offset.x = b->map->bloc_size;
	else
		offset.x = -b->map->bloc_size;
	offset.y = b->map->bloc_size / tan(angle);
	while (wall == 0 && cur_point.y < b->map->px_height && cur_point.y > 0)
	{
		if (get_grid(b->map, cur_point.x, cur_point.y,1) == 1) 
			wall = 1;
		cur_point.x += offset.x;
		cur_point.y += offset.y;
	}
	return (cur_point);
}

void draw_ray(t_player *p, t_map *m, double angle)
{
	t_point cur_h;
	t_point cur_v;
	t_point p_pos;
//	double ray_dist;

	p_pos = to_grid(p->pos->x, p->pos->y, m);
	cur_h = closest_grid_h(p->pos, m, angle);
	cur_v = closest_grid_v(p->pos, m, angle);
	ft_putchar('\n');
	printf("Angle: %f\n", angle);
	ft_putstr(YELO"h");
	disp_point(&p_pos);
	ft_putstr(CYAN"h");
	disp_point(&cur_h);
	ft_putstr(GRN"v");
	disp_point(&cur_v);
	ft_putstr(RST);
	if (cur_h.x > 0 && cur_h.y > 0)
	{
		p->ctx->line(map_scaled(p->pos, m), map_scaled(&cur_h, m), p->ctx);
	}

}