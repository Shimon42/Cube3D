/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:09:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/04 16:30:02 by siferrar         ###   ########lyon.fr   */
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
			p->z += step * (p->bob_height * p->speedRatio);
			if (p->z > p->bob_height)
			{
				p->bobbing = -1;
				p->z = p->bob_height;
			}
		}
		else
		{
			p->z -= step * (p->bob_height * p->speedRatio);
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
	t_map	*m;
	t_brain	*b;
	int		key;

	b = (t_brain *)p->brain;
	p->speedRatio = 1.0/(b->ctx->fps + 1);
	m = b->map;
	if ((key = get_grid(m,
		p->pos->x + p->speed * (cos(p->angle + (ft_inrad(90)) * dir)) * p->speedRatio,
								p->pos->y, 1)) != 1 && key != 2 && key != 4)
		p->pos->x += p->speed * (cos(p->angle + (ft_inrad(90)) * dir)) * p->speedRatio;
	if ((key = get_grid(m, p->pos->x,
		p->pos->y + p->speed * (sin(p->angle + (ft_inrad(90)) * dir)) * p->speedRatio,
											1)) != 1 && key != 2 && key != 4)
		p->pos->y += p->speed * (sin(p->angle + (ft_inrad(90)) * dir)) * p->speedRatio;
	p->as_move = 1;
	if (is_key_pressed(b, 13) == -1 && is_key_pressed(b, 1) == -1)
		bobbing(p);
}

void	move(struct s_player *p, int dir)
{
	t_map	*m;
	t_brain	*b;
	int		key;

	b = (t_brain *)p->brain;
	m = b->map;
	p->speedRatio = 1.0/(b->ctx->fps + 1);
	if ((key = get_grid(m, p->pos->x + p->step->x * dir * p->speedRatio, p->pos->y, 1))
											!= 1 && key != 2 && key != 4)
		p->pos->x += p->step->x * dir * p->speedRatio;
	if ((key = get_grid(m, p->pos->x, p->pos->y + p->step->y * dir * p->speedRatio, 1))
											!= 1 && key != 2 && key != 4)
		p->pos->y += p->step->y * dir * p->speedRatio;
	p->as_move = 1;
	bobbing(p);
}

void	rotate(struct s_player *p, float angle)
{
	p->angle += angle;
	if (p->angle > 2 * PI)
		p->angle = p->angle - 2 * PI;
	else if (p->angle <= 0)
		p->angle = 2 * PI - p->angle;
	p->step->x = (p->pos->x + p->speed * cos(p->angle)) - p->pos->x;
	p->step->y = (p->pos->y + p->speed * sin(p->angle)) - p->pos->y;
	p->divided = p->angle - (p->cam->fov / 2);
	p->as_rotate = 1;
	p->as_move = 1;
}

void	jump(t_player *p, float speed)
{
	double	jump_h;
	t_brain	*b;

	b = (t_brain *)p->brain;
	jump_h = (double)b->map->bloc_size * 0.9;
	speed *= jump_h * (p->speedRatio);
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
	b->player->as_move = 1;
}
