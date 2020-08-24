/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fullmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:30:05 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/24 10:45:04 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"

void		calculate_size_mm(t_brain *b, int *margin,
												float *mrgn_top)
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
	b->player->as_move = 1;
	if (*ease < 1 && *ease + ease_val <= 1)
		*ease += ease_val;
	else
		*ease = 1;
}

void		draw_fullmap(t_brain *b, float ease_val)
{
	int				margin;
	float			mrgn_top;
	static float	ease = 0.0;

	if (ease_val > 0)
	{
		mrgn_top = 0;
		margin = 100;
		calculate_size_mm(b, &margin, &mrgn_top);
		ease_in_n_out(b, &ease, ease_val);
		draw_minimap(b,
			margin,
			mrgn_top,
			(b->ctx->width - 2 * margin) * (ease));
	}
	else
		ease = 0;
}
