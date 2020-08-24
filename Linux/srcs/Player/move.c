/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:09:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/24 13:10:05 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	bobbing(t_player *p)
{
	static float	step = -1;

	step = (step == -1 ? p->bob_height / 1.3 : step);
	if (p->jumping == 0)
	{
		if (p->bobbing == 1)
		{
			p->z += step * (p->bob_height * p->speed_ratio);
			if (p->z > p->bob_height)
			{
				p->bobbing = -1;
				p->z = p->bob_height;
			}
		}
		else
		{
			p->z -= step * (p->bob_height * p->speed_ratio);
			if (p->z <= 0)
			{
				p->bobbing = 1;
				p->z = 0;
			}
		}
	}
}

void	side_move(struct s_player *p, int dir)
{
	t_map		*m;
	t_brain		*b;
	int			res;
	t_fpoint	new;

	b = (t_brain *)p->brain;
	m = b->map;
	new.x = p->pos->x + p->speed * (cos(p->angle + (ft_inrad(90)) * dir))
				* p->speed_ratio;
	new.y = p->pos->y + p->speed * (sin(p->angle + (ft_inrad(90)) * dir))
				* p->speed_ratio;
	if ((res = get_grid(m, new.x, p->pos->y, 1)) != 1
		&& !(res >= 2 && res <= 4))
		p->pos->x = new.x;
	if ((res = get_grid(m, p->pos->x, new.y, 1)) != 1
		&& !(res >= 2 && res <= 4))
		p->pos->y = new.y;
	if (is_key_pressed(b, 13) == -1 && is_key_pressed(b, 1) == -1)
		bobbing(p);
}

void	move(struct s_player *p, int dir)
{
	t_map		*m;
	t_brain		*b;
	int			res;
	t_fpoint	new;

	b = (t_brain *)p->brain;
	m = b->map;
	new.x = p->pos->x + p->step->x * dir * p->speed_ratio;
	new.y = p->pos->y + p->step->y * dir * p->speed_ratio;
	if ((res = get_grid(m, new.x, p->pos->y, 1)) != 1
		&& !(res >= 2 && res <= 4))
		p->pos->x = new.x;
	if ((res = get_grid(m, p->pos->x, new.y, 1)) != 1
		&& !(res >= 2 && res <= 4))
		p->pos->y = new.y;
	bobbing(p);
}

void	rotate(struct s_player *p, float angle)
{
	p->angle += (angle * p->speed_ratio);
	p->angle = ft_to_360(p->angle);
	p->step->x = (p->pos->x + p->speed * cos(p->angle)) - p->pos->x;
	p->step->y = (p->pos->y + p->speed * sin(p->angle)) - p->pos->y;
	p->divided = p->angle - (p->cam->fov / 2);
}

void	jump(t_player *p, float speed)
{
	double	jump_h;
	t_brain	*b;

	b = (t_brain *)p->brain;
	jump_h = (double)b->map->bloc_size * 0.9;
	speed *= jump_h * (p->speed_ratio);
	if (speed > 0 && p->jumping == 0)
		p->jumping = 1;
	if (p->jumping != 0)
	{
		if (p->z < jump_h || (p->jumping == -1 && speed < 0))
			p->z += speed * p->jumping;
		else if (p->jumping == 1)
		{
			p->z = jump_h - 0.1;
			p->jumping = -1;
		}
		if (p->z < 0)
		{
			p->jumping = 0;
			p->z = 0;
		}
	}
}
