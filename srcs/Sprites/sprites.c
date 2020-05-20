/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:35:34 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		draw_sprite(void *brain, t_sprite *s, float col)
{
	t_brain		*b;
	t_fpoint	s_size;
	t_fpoint	s_dist;
	t_fpoint	ratio;
	double		angle;
	int			start_y;
	int			start_x;
	int			color;
	int			y;
	int			x;

	b = (t_brain *)brain;
	s_dist = new_fpoint(s->pos.x - b->player->pos->x,
						s->pos.y - b->player->pos->y);
	s_size = new_fpoint((b->map->bloc_size / s->dist) * b->player->cam->proj_dist
				, (b->map->bloc_size / s->dist) * b->player->cam->proj_dist);
	angle = ft_indeg(ft_to_360(b->player->angle - atan2(s_dist.y, s_dist.x)));
	col = b->ctx->width / ft_indeg(b->player->cam->fov);
	if (angle >= 0 && angle < 180)
		start_x = (int)floor(b->ctx->width / 2 - (col * angle));
	else if (angle < 360)
		start_x = (int)floor(b->ctx->width / 2 + (col * (360 - angle)));
	if ((start_x -= s_size.x / 2) + s_size.x < 0)
		return ;
	start_y = (b->ctx->height / 2) * (1 + (1 / s->dist)) + b->player->z - s_size.y / 2;
	ratio = new_fpoint(s->model->width / s_size.x, s->model->height / s_size.y);
	x = 0;
	while (x < s_size.x)
	{
		if (b->map->sprites->column[start_x + x] >= floor(s->dist))
		{
			if (start_x + x > 0 && start_x + x < b->ctx->width)
			{
				y = 0;
				while (y < s_size.y)
				{
					if (start_y + y > 0 && start_y + y < b->ctx->height)
					{
						color = pixel_get(s->model, x * ratio.x, y * ratio.y);
						if (s->shadow != NULL)
						{
							col = pixel_get(s->shadow, x * ratio.x, y * ratio.y);
							if (col != SPR_TRANSP)
							{
								col = opacity(pixel_get(b->map->frame, start_x + x, start_y + y), col, 0.4);
								pixel_put(start_x + x, start_y + y, col, b->map->frame);
							}
						}
						if (color != SPR_TRANSP)
							pixel_put(start_x + x, start_y + y, color, b->map->frame);
					}
					y++;
				}
			}
		}
		x++;
	}
}
