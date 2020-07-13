/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fullmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:30:05 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 13:16:07 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"

void		calculate_size_mm(t_brain *b, int *margin,
												float *mrgn_top, float *ease)
{
	float scale;

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

void		draw_fullmap(t_brain *b, float ease_val)
{
	int				margin;
	float			mrgn_top;
	static float	ease = 0;

	margin = 100;
	if (ease_val > 0)
	{
		calculate_size_mm(b, &margin, &mrgn_top, &ease);
		draw_minimap(b,
			margin,
			mrgn_top,
			(b->ctx->width - 2 * margin) * (ease));
		ease_in_n_out(b, &ease, ease_val);
	}
	else
	{
		if (ease != 0)
			b->player->as_move = 1;
		else
			b->player->as_move = 0;
		ease = 0;
	}
}
