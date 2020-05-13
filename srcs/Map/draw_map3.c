/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:29:44 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/13 13:45:47 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		point_on_map(t_brain *b, int x, int y, int color)
{
	t_fpoint p;

	p = new_point(x, y);
	p = map_scaled(&p, b->map);
	b->ctx->color = color;
	b->ctx->circle(b->map->disp.x + p.x, b->map->disp.y + p.y,
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

void		draw_elem(t_brain *b, int disp_x, int disp_y, float scale, int val)
{
	b->ctx->color = get_map_colors(val);
	b->ctx->rect(disp_x, disp_y,
				b->map->bloc_size * scale + 1,
				b->map->bloc_size * scale + 1,
				1,
				b->ctx);
	if (b->map->scale > 0.1)
	{
		b->ctx->color = 0x222222;
		b->ctx->rect(disp_x,
				disp_y,
				b->map->bloc_size * scale + 1,
				b->map->bloc_size * scale + 1,
				0,
				b->ctx);
	}
}

void		draw_elems(t_brain *b, int disp_x, int disp_y, float scale)
{
	int			y;
	int			x;
	int			val;
	t_fpoint	p_pos;

	y = 0;
	p_pos = to_grid(b->player->pos->x, b->player->pos->y, b->map);
	while (y < b->map->height)
	{
		x = 0;
		while (x < b->map->width)
		{
			if ((val = get_grid(b->map, x, y, 0)) >= 0)
				draw_elem(b, floor(disp_x + (x * (b->map->bloc_size * scale))),
				floor(disp_y + (y * (b->map->bloc_size * scale))), scale, val);
			x++;
		}
		y++;
	}
	b->ctx->color = 0xFFFF00;
	b->ctx->rect(floor(disp_x + (p_pos.x * (b->map->bloc_size * scale))),
			floor(disp_y + (p_pos.y * (b->map->bloc_size * scale))),
			b->map->bloc_size * scale, b->map->bloc_size * scale, 0, b->ctx);
}

void		line_on_map(t_brain *b, t_fpoint p1, t_fpoint p2)
{
	p1 = map_scaled(&p1, b->map);
	p2 = map_scaled(&p2, b->map);
	b->ctx->line(new_point(b->map->disp.x + p1.x, b->map->disp.y + p1.y),
			new_point(b->map->disp.x + p2.x, b->map->disp.y + p2.y),
			b->ctx);
}
