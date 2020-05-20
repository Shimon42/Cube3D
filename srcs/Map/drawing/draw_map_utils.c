/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:39:56 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:45:48 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"

void		point_on_map(t_brain *b, int x, int y, int color)
{
	t_fpoint	p;
	t_fpoint	pos;

	p = new_fpoint(x, y);
	p = map_scaled(&p, b->map);
	b->ctx->color = color;
	pos = new_fpoint(b->map->disp.x + p.x, b->map->disp.y + p.y);
	b->ctx->circle(pos,
						(b->map->bloc_size * 0.06) * b->map->scale, 1, b->ctx);
}

int			get_map_colors(int val)
{
	if (val == 0)
		return (0);
	else if (val == 1)
		return (0x00FFFF);
	else if (val >= 2 && val < 5)
		return (0x00FF00);
	else if (val == 'N' - '0' || val == 'E' - '0'
			|| val == 'S' - '0' || val == 'W' - '0')
		return (0xCCFFFFFF);
	else
		return (0xFF00FF);
}

void		line_on_map(t_brain *b, t_fpoint p1, t_fpoint p2)
{
	p1 = map_scaled(&p1, b->map);
	p2 = map_scaled(&p2, b->map);
	b->ctx->line(new_point(b->map->disp.x + p1.x, b->map->disp.y + p1.y),
			new_point(b->map->disp.x + p2.x, b->map->disp.y + p2.y),
			b->ctx);
}
