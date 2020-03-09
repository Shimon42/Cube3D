/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:31:18 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/09 20:15:03 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"


/*
**	1. Take the pixel.
**	2. Draw a line (a ray) from the pixel to the viewers eye. 
**	3. Extends the line so that it intersect the floor.
**	4. The point where the line "intersect" the floor is the point on 
** 		the texture map that is being hit by the ray.
**	5. Take the pixel value of that point on the texture map and draw it on the screen.
**	* Repeat 1-5 until the bottom of the screen is reached.
**
** https://www.permadi.com/tutorial/raycast/images/figure25.gif
** https://www.permadi.com/tutorial/raycast/images/figure26.gif
*/

void draw_floor(t_brain *b, t_ctx *c, double w_start, double col)
{
	int i;
	int color;
	t_buff *floor;

	floor = b->map->floor;
	i = w_start;
	while (i < b->ctx->height)
	{
		color = pixel_get(*floor, ((int)floor(col)) % 64, (i + 1) * ratio.y);
		i++;
	}
}