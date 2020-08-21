/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/21 11:17:51 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		draw_sprite_col(t_brain *b, t_sprite *s, t_draw_spr *drw)
{
	int color;

	while (drw->y < drw->size.y)
	{
		if (drw->start.y + drw->y > 0 && drw->start.y + drw->y < b->ctx->height)
		{
			if (s->shadow != NULL)
			{
				color = pixel_get(s->shadow, drw->x * drw->ratio.x,
					drw->y * drw->ratio.y);
				if (color != SPR_TRANSP)
				{
					color = opacity(pixel_get(b->map->frame,
					drw->start.x + drw->x, drw->start.y + drw->y), color, 0.4);
					pixel_put(drw->start.x + drw->x, drw->start.y + drw->y,
						color, b->map->frame);
				}
			}
			if ((color = pixel_get(s->model, drw->x * drw->ratio.x,
				drw->y * drw->ratio.y)) != SPR_TRANSP)
				pixel_put(drw->start.x + drw->x, drw->start.y + drw->y,
				color, b->map->frame);
		}
		drw->y++;
	}
}

void		draw_sprite_row(t_brain *b, t_sprite *s, t_draw_spr *s_draw)
{
	s_draw->x = ((s_draw->start.x < 0) ? (s_draw->start.x) * -1 : 0);
	while (s_draw->x < s_draw->size.x)
	{
		if (s_draw->start.x + s_draw->x < b->ctx->width)
		{
			if (b->map->sprites->column[s_draw->start.x + s_draw->x]
				>= floor(s->dist))
			{
				if (s_draw->start.x + s_draw->x > 0)
				{
					s_draw->y = 0;
					draw_sprite_col(b, s, s_draw);
				}
			}
		}
		else
			break ;
		s_draw->x++;
	}
}

void		calc_good_start(t_brain *b, float col,
				double angle, t_draw_spr *drw)
{
	if (angle >= 0 && angle < 180)
		drw->start.x = (int)floor(b->ctx->width / 2 - (col * angle));
	else if (angle < 360)
		drw->start.x = (int)floor(b->ctx->width / 2 + (col * (360 - angle)));
	if ((drw->start.x -= drw->size.x / 2) + drw->size.x < 0)
		return ;
}

void		draw_sprite(void *brain, t_sprite *s, float col)
{
	t_brain		*b;
	t_fpoint	s_dist;
	t_draw_spr	s_draw;
	double		angle;
	float		dist_y;

	b = (t_brain *)brain;
	s_dist = new_fpoint(s->pos.x - b->player->pos->x,
						s->pos.y - b->player->pos->y);
	angle = ft_to_360(b->player->angle - atan2(s_dist.y, s_dist.x));
	dist_y = s->dist * cos(angle);
	angle = ft_indeg(angle);
	s_draw.size = new_fpoint((b->map->bloc_size / s->dist)
					* b->player->cam->proj_dist
				, (b->map->bloc_size / dist_y) * b->player->cam->proj_dist);
	col = b->ctx->width / ft_indeg(b->player->cam->fov);
	calc_good_start(b, col, angle, &s_draw);
	s_draw.start.y = (b->ctx->height / 2) *
		(1 + (1 / s->dist)) + b->player->z - s_draw.size.y / 2;
	s_draw.ratio = new_fpoint(s->model->width / s_draw.size.x,
								s->model->height / s_draw.size.y);
	draw_sprite_row(b, s, &s_draw);
}
