/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 20:56:28 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/14 21:16:05 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void put_image(t_ctx *c, t_buff *img, t_fpoint pos, int width, int height)
{
	t_point pos;
	t_fpoint ratio;
	t_fpoint s_size;
	int color;

	ratio.x = img->width / width;
	ratio.y = img->height / height;
	while (pos.y < s_size.y)
	{
		color = pixel_get(img, col * ratio.x, y * ratio.y);

		pixel_put(col, y, color, b->map->frame);
		y++;
	}

}