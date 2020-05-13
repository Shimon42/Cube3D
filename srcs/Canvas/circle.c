/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:58:38 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/13 12:44:36 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	draw_outer(float c_x, float c_y, int x, int y, t_ctx *ctx)
{
	pixel_put(c_x + x, c_y + y, ctx->color, ctx->cur_buff);
	pixel_put(c_x + y, c_y + x, ctx->color, ctx->cur_buff);
	pixel_put(c_x - x, c_y + y, ctx->color, ctx->cur_buff);
	pixel_put(c_x - y, c_y + x, ctx->color, ctx->cur_buff);
	pixel_put(c_x + x, c_y - y, ctx->color, ctx->cur_buff);
	pixel_put(c_x + y, c_y - x, ctx->color, ctx->cur_buff);
	pixel_put(c_x - x, c_y - y, ctx->color, ctx->cur_buff);
	pixel_put(c_x - y, c_y - x, ctx->color, ctx->cur_buff);
}

void	condition(int *d, int *x, int *y, int ray)
{
	if (*d >= 2 * *x)
	{
		*d -= 2 * *x + 1;
		(*x)++;
	}
	else if (*d < 2 * (ray - *y))
	{
		*d += 2 * *y - 1;
		(*y)--;
	}
	else
	{
		*d += 2 * (*y - *x - 1);
		(*y)--;
		(*x)++;
	}
}

void	draw_circle(float c_x, float c_y, int ray, int fill, t_ctx *ctx) // enlever le fill, tout le temps a 1
{
	int	x;
	int	y;
	int	d;

	while ((fill == 1 && ray > 0) || fill == 0)
	{
		x = 0;
		y = ray;
		d = ray - 1;
		while (y >= x)
		{
			draw_outer(c_x, c_y, x, y, ctx);
			condition(&d, &x, &y, ray);
		}
		if (!fill)
			return ;
		ray--;
	}
	pixel_put(c_x, c_y, ctx->color, ctx->cur_buff);
}
