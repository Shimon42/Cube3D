/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:53:35 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/24 09:14:47 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		get_sky_color(t_brain *b, t_fpoint ratio, float offset, int y)
{
	if (b->map->skybox->is_color != -1)
		return (b->map->skybox->is_color);
	else
		return (pixel_get(b->map->skybox,
							offset * ratio.x,
							b->player->z * -0.2 + y * ratio.y + 180));
}

void	draw_sky(t_brain *b, double col, double end)
{
	int				color;
	int				y;
	static t_fpoint ratio = {-420, -420};
	static float	width = 0;
	float			left;

	if (ratio.x == -420)
	{
		ratio.y = (float)b->map->skybox->height / (b->player->cam->proj_size.y);
		width = (float)b->player->cam->proj_size.x *
			((2 * PI) / b->player->cam->fov);
		ratio.x = b->map->skybox->width / width;
	}
	y = 0;
	left = width * (b->player->angle / (2.0 * PI));
	while (y < end)
	{
		color = get_sky_color(b, ratio, (col + left), y);
		pixel_put(col, y, color, b->map->frame);
		y++;
	}
}
