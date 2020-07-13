/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:29:42 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/20 15:38:11 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int			get_grid(t_map *m, int x, int y, int need_rescale)
{
	t_fpoint	scaled;
	int			val;

	if (x >= 0 && y >= 0)
	{
		if (need_rescale)
		{
			if (x < m->px_width && y < m->px_height)
			{
				scaled = to_grid(x, y, m);
				x = scaled.x;
				y = scaled.y;
			}
			else
				return (-1);
		}
		if (y < m->height && x < m->grid[y]->length)
		{
			val = m->grid[y]->line[x];
			return (val);
		}
	}
	return (-1);
}

t_fpoint	to_grid(int x, int y, t_map *m)
{
	t_fpoint ret;

	ret.x = x / m->bloc_size;
	ret.y = y / m->bloc_size;
	return (ret);
}

t_fpoint	map_fscaled(t_fpoint *p, t_map *m)
{
	t_fpoint ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return (ret);
}

t_fpoint	map_scaled(t_fpoint *p, t_map *m)
{
	t_fpoint ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return (ret);
}

void		draw_frame(t_brain *b)
{
	b->ctx->color = 0x000000;
	b->ctx->rect(new_point(b->map->disp.x, b->map->disp.y),
				new_point(b->map->bloc_size * b->map->width * b->map->scale,
				b->map->bloc_size * b->map->height * b->map->scale),
				1,
				b->ctx);
}
