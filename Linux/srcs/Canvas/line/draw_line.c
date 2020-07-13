/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:20:40 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:41:33 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/my_canvas.h"

void	calc_quads(t_ctx *ctx, t_point *p1, t_point *p2, t_fpoint *diff)
{
	if (diff->x > 0)
	{
		if ((diff->y = p2->y - p1->y) != 0)
		{
			if (diff->y > 0)
				calc_first_quad(ctx, *p1, *p2, *diff);
			else
				calc_fourth_quad(ctx, *p1, *p2, *diff);
		}
		else
			while (p1->x != p2->x)
				pixel_put(p1->x++, p1->y, ctx->color, ctx->cur_buff);
	}
	else if ((diff->y = p2->y - p1->y) != 0)
	{
		if (diff->y > 0)
			calc_second_quad(ctx, *p1, *p2, *diff);
		else
			calc_third_quad(ctx, *p1, *p2, *diff);
	}
	else
		while (p1->x != p2->x)
			pixel_put(p1->x--, p1->y, ctx->color, ctx->cur_buff);
}

void	draw_line(t_point p1, t_point p2, t_ctx *ctx)
{
	t_fpoint diff;

	diff = new_fpoint(0, 0);
	if ((diff.x = p2.x - p1.x) != 0)
	{
		calc_quads(ctx, &p1, &p2, &diff);
	}
	else
	{
		if ((diff.y = p2.y - p1.y) != 0)
		{
			if (diff.y > 0)
			{
				while (p1.y != p2.y)
					pixel_put(p1.x, p1.y++, ctx->color, ctx->cur_buff);
			}
			else
			{
				while (p1.y != p2.y)
					pixel_put(p1.x, p1.y--, ctx->color, ctx->cur_buff);
			}
		}
	}
}
