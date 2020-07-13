/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:53:35 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/13 15:13:38 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	draw_sky(t_brain *b, double col, double end)
{
	int				color;
	int				y;
	static t_fpoint ratio = {-420, -420};
	static float	width = 0;
	float			left;

	if (ratio.x == -420)
	{
		ratio.y = (float)b->map->skybox->height / b->player->cam->proj_size.y;
		width = b->player->cam->proj_size.x * ((2 * PI) / b->player->cam->fov);
		ratio.x = (float)b->map->skybox->width / width;
	}
	y = 0;
	left = -width * (b->player->angle / (2 * PI));
	if (left < width - b->player->cam->proj_size.x)
		left += width;
	while (y < end)
	{
		color = pixel_get(b->map->skybox,
							col - left * ratio.x,
							200 - b->player->z * 0.1 + y * ratio.y);
		pixel_put(col, y, color, b->map->frame);
		y++;
	}
}
