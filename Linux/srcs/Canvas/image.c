/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 18:48:51 by user42            #+#    #+#             */
/*   Updated: 2020/08/20 19:32:25 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include "../../includes/cube3d.h"

void	put_image(t_buff *out, t_buff *img, t_point pos, t_point size)
{
	t_draw_spr	drw;
	int			color;

	drw.start.x = pos.x;
	drw.start.y = pos.y;
	drw.ratio.x = img->width / (float)size.x;
	drw.ratio.y = img->height / (float)size.y;
	drw.x = 0;
	drw.y = 0;
	while (drw.x < size.x)
	{
		drw.y = 0;
		while (drw.y < size.y)
		{
			color = pixel_get(img, drw.x * drw.ratio.x, drw.y * drw.ratio.y);
			if (color != SPR_TRANSP)
				pixel_put(drw.start.x + drw.x, drw.start.y + drw.y,
					color, out);
			drw.y++;
		}
		drw.x++;
	}
}
