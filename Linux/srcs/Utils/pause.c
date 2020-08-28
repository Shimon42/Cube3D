/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 19:29:17 by user42            #+#    #+#             */
/*   Updated: 2020/08/28 08:01:15 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	disp_pause(t_brain *b)
{
	t_buff	*img;
	int		margin;
	float	scale;
	t_point	strt;

	if (b->is_paused != 1)
		return ;
	ft_putstr("Pause Menu\n");
	margin = b->ctx->width * 0.2;
	img = b->pause_menu;
	scale = ((float)((b->ctx->width - 2 * margin) /
						(float)img->width));
	strt.x = (b->ctx->width / 2) - (img->width * scale) / 2;
	strt.y = (b->ctx->height / 2) - ((img->height * scale) / 2);
	put_image(b->map->frame, img, strt,
		new_point(img->width * scale, img->height * scale));
	mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr,
		b->map->frame->img, 0, 0);
	free(b->keys);
	init_keys(b);
	b->is_paused = 2;
}
