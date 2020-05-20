/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:58:38 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:11:20 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	draw_outer(t_fpoint pos, int x, int y, t_ctx *ctx)
{
	pixel_put(pos.x + x, pos.y + y, ctx->color, ctx->cur_buff);
	pixel_put(pos.x + y, pos.y + x, ctx->color, ctx->cur_buff);
	pixel_put(pos.x - x, pos.y + y, ctx->color, ctx->cur_buff);
	pixel_put(pos.x - y, pos.y + x, ctx->color, ctx->cur_buff);
	pixel_put(pos.x + x, pos.y - y, ctx->color, ctx->cur_buff);
	pixel_put(pos.x + y, pos.y - x, ctx->color, ctx->cur_buff);
	pixel_put(pos.x - x, pos.y - y, ctx->color, ctx->cur_buff);
	pixel_put(pos.x - y, pos.y - x, ctx->color, ctx->cur_buff);
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

void	draw_circle(t_fpoint pos, int ray, int fill, t_ctx *ctx)
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
			draw_outer(pos, x, y, ctx);
			condition(&d, &x, &y, ray);
		}
		if (!fill)
			return ;
		ray--;
	}
	pixel_put(pos.x, pos.y, ctx->color, ctx->cur_buff);
}
