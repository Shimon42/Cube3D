/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:36:41 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/13 15:04:30 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		draw_player_map(t_brain *b, t_player *p, t_fpoint m_pos)
{
	b->ctx->color = 0xFFFFFF;
	b->ctx->circle(m_pos.x + (p->pos->x * b->map->scale),
					m_pos.y + (p->pos->y * b->map->scale),
					(b->map->bloc_size * 0.1) * b->map->scale,
					1,
					b->ctx);
	draw_minimap_closest(b, m_pos, p->angle);
	b->ctx->color = 0xFF0000;
	draw_minimap_closest(b, m_pos, to_360(p->angle - p->cam->fov / 2));
	b->ctx->color = 0x00FF00;
	draw_minimap_closest(b, m_pos, p->angle + p->cam->fov / 2);
}
