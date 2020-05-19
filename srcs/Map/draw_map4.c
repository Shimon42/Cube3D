/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:36:41 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/19 15:24:06 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		draw_player_map(t_brain *b, t_player *p, t_fpoint m_pos)
{
	t_fpoint position;

	b->ctx->color = 0xFFFFFF;
	position = new_point(m_pos.x + (p->pos->x * b->map->scale), m_pos.y + (p->pos->y * b->map->scale));
	b->ctx->circle(&position,
					(b->map->bloc_size * 0.1) * b->map->scale,
					1,
					b->ctx);
	draw_minimap_closest(b, m_pos, p->angle);
	b->ctx->color = 0xFF0000;
	draw_minimap_closest(b, m_pos, to_360(p->angle - p->cam->fov / 2));
	b->ctx->color = 0x00FF00;
	draw_minimap_closest(b, m_pos, p->angle + p->cam->fov / 2);
}

void		calculate_size_mm(t_brain *b, int *margin,
												float *mrgn_top, float *ease)
{
	int scale;

	*margin = 100 * b->map->scale;
	if (b->map->px_height > b->map->px_width)
		scale = ((float)((b->ctx->height - 2 * *margin) /
						(float)b->map->height));
	else
		scale = ((float)((b->ctx->width - 2 * *margin) /
						(float)b->map->px_width));
	if (b->map->px_width * scale > b->ctx->width)
		scale = ((float)((b->ctx->height - 2 * *margin) /
						(float)b->map->px_height));
	b->map->scale = scale;
	*mrgn_top = (b->ctx->height -
				(b->map->height * b->map->bloc_size * scale)) / 2;
}

void		ease_in_n_out(t_brain *b, float *ease, float ease_val)
{
	if (*ease < 1 && *ease + ease_val <= 1)
	{
		*ease += ease_val;
		b->player->as_move = 1;
	}
	else if (b->player->as_move == 0 && *ease == 1)
	{
		b->player->as_move = 1;
		*ease = 1.000001;
	}
	else if (*ease != 1 && *ease != 1.000001)
	{
		*ease = 1;
		b->player->as_move = 1;
	}
}
