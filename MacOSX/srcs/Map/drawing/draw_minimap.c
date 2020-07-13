/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:43:45 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:39:38 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"

void		draw_elem(t_brain *b, int disp_x, int disp_y, int val)
{
	b->ctx->color = get_map_colors(val);
	b->ctx->rect(new_point(disp_x, disp_y),
				new_point(b->map->bloc_size * b->map->scale + 1,
					b->map->bloc_size * b->map->scale + 1),
				1,
				b->ctx);
	if (b->map->scale > 0.1)
	{
		b->ctx->color = 0x222222;
		b->ctx->rect(new_point(disp_x, disp_y),
				new_point(b->map->bloc_size * b->map->scale + 1,
					b->map->bloc_size * b->map->scale + 1),
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
				floor(disp_y + (y * (b->map->bloc_size * scale))), val);
			x++;
		}
		y++;
	}
	b->ctx->color = 0xFFFF00;
	b->ctx->rect(
			new_point(floor(disp_x + (p_pos.x * (b->map->bloc_size * scale))),
				floor(disp_y + (p_pos.y * (b->map->bloc_size * scale)))),
			new_point(b->map->bloc_size * scale, b->map->bloc_size * scale),
			0, b->ctx);
}

void		draw_player_map(t_brain *b, t_player *p, t_fpoint m_pos)
{
	t_fpoint position;

	b->ctx->color = 0xFFFFFF;
	position = new_fpoint(m_pos.x + (p->pos->x * b->map->scale),
						m_pos.y + (p->pos->y * b->map->scale));
	b->ctx->circle(position,
					(b->map->bloc_size * 0.1) * b->map->scale,
					1,
					b->ctx);
	draw_minimap_closest(b, m_pos, p->angle);
	b->ctx->color = 0xFF0000;
	draw_minimap_closest(b, m_pos, ft_to_360(p->angle - p->cam->fov / 2));
	b->ctx->color = 0x00FF00;
	draw_minimap_closest(b, m_pos, p->angle + p->cam->fov / 2);
}

void		draw_minimap(t_brain *b, int x, int y, int width)
{
	float scale;

	b->ctx->cur_buff = b->map->frame;
	if (b->map->px_height > b->map->px_width)
		scale = ((float)(width / (float)b->map->px_height));
	else
		scale = ((float)(width / (float)b->map->px_width));
	if (b->map->px_height * scale > b->ctx->height)
	{
		scale = ((float)((b->ctx->height - 2 *
						(100 * b->map->scale)) / (float)b->map->px_height));
		x = (b->ctx->width - (b->map->width * b->map->bloc_size * scale)) / 2;
		y = (b->ctx->height - (b->map->height * b->map->bloc_size * scale)) / 2;
	}
	b->map->scale = scale;
	b->map->disp.x = floor(x);
	b->map->disp.y = floor(y);
	draw_elems(b, x, y, scale);
	draw_player_map(b, b->player, new_fpoint(x, y));
}
