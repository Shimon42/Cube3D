/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:31:18 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/10 10:36:13 by siferrar         ###   ########lyon.fr   */
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

void draw_floor(t_brain *b, t_ctx *c, t_detect w, double w_start, double col)
{
	int i;
	int color;
	t_buff *floor_t;
	t_fpoint ratio;
	double dist;
	double x,y;
	double cur_angle = b->player->angle - (b->player->cam->fov / 2) + (b->player->cam->fov/ c->width * col);;
	floor_t = b->map->floor;
	i = w_start;


	while (i < b->ctx->height)
	{
		dist = (((double)b->map->bloc_size/2) / (i - (b->player->cam->proj_size.y/2))) * b->player->cam->proj_dist;
		ratio.x =  floor_t->width % (int)floor(dist);
		x = dist * cos(cur_angle) + b->player->pos->x;
		y = dist * sin(cur_angle) + b->player->pos->y;

		color = pixel_get(floor_t, (int)floor(x) % floor_t->width, (int)floor(y) % floor_t->height);
		pixel_put_buff(col, i, color, b->map->frame);
		i++;
	}
}