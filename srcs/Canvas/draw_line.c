/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:20:40 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/23 10:21:45 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/my_canvas.h"

void calc_first_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;
	
	if (diff.x >= diff.y) // first octant
	{
		diff.x = (e = diff.x) * 2;
		diff.y *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (++p1.x == p2.x)
				break;
			if ((e -= diff.y) < 0)
			{
				p1.y++;  // déplacement diagonal
				e += diff.x ;
			}
		}
	}
	else // second octant
	{
		diff.y = (e = diff.y) * 2;
		diff.x *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (++p1.y == p2.y)
				break;
			if ((e -= diff.x) < 0)
			{
				p1.x++;  // déplacement diagonal
				e += diff.y ;
			}
		}
	}
}
void calc_fourth_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;
	
	if (diff.x >= -diff.y) // octant 8
	{
		diff.x = (e = diff.x) * 2;
		diff.y *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (++p1.x == p2.x)
				break;
			if ((e += diff.y) < 0)
			{
				p1.y--;  // déplacement diagonal
				e += diff.x ;
			}
		}
	}
	else // octant 7
	{
		diff.y = (e = diff.y) * 2;
		diff.x *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (--p1.y == p2.y)
				break;
			if ((e += diff.x) > 0)
			{
				p1.x++;  // déplacement diagonal
				e += diff.y ;
			}
		}
	}
}

void calc_second_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;
	
	if (-diff.x >= diff.y) //  octant 4
	{
		diff.x = (e = diff.x) * 2;
		diff.y *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (--p1.x == p2.x)
				break;
			if ((e += diff.y) >= 0)
			{
				p1.y++;  // déplacement diagonal
				e += diff.x ;
			}
		}
	}
	else // octant 3
	{
		diff.y = (e = diff.y) * 2;
		diff.x *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (++p1.y == p2.y)
				break;
			if ((e += diff.x) <= 0)
			{
				p1.x--;  // déplacement diagonal
				e += diff.y ;
			}
		}
	}
}
void calc_third_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;
	
	if (diff.x <= diff.y) // octant 8
	{
		diff.x = (e = diff.x) * 2;
		diff.y *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (--p1.x == p2.x)
				break;
			if ((e -= diff.y) >= 0)
			{
				p1.y--;  // déplacement diagonal
				e += diff.x ;
			}
		}
	}
	else // octant 7
	{
		diff.y = (e = diff.y) * 2;
		diff.x *= 2;
		while (1)
		{  // déplacements horizontaux
			pixel_put(p1.x, p1.y, ctx->color,  ctx->cur_buff);
			if (--p1.y == p2.y)
				break;
			if ((e -= diff.x) >= 0)
			{
				p1.x--;  // déplacement diagonal
				e += diff.y ;
			}
		}
	}
}

void draw_line(t_fpoint p1, t_fpoint p2, t_ctx *ctx)
{
	t_fpoint diff;

	diff = new_point(0, 0);
	if ((diff.x = p2.x - p1.x) != 0)
	{
		if (diff.x > 0)
		{
			if ((diff.y = p2.y - p1.y) != 0)
			{
				if (diff.y > 0)
					calc_first_quad(ctx, p1, p2, diff);
				else
					calc_fourth_quad(ctx, p1, p2, diff);
			}
			else
				while (p1.x != p2.x)
					pixel_put(p1.x++, p1.y, ctx->color, ctx->cur_buff);
		}
		else
		{
			if ((diff.y = p2.y - p1.y) != 0)
			{
				if (diff.y > 0)
					calc_second_quad(ctx, p1, p2, diff);
				else
					calc_third_quad(ctx, p1, p2, diff);
			}
			else
				while (p1.x != p2.x)
					pixel_put(p1.x--, p1.y, ctx->color, ctx->cur_buff) ;
		}
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
					pixel_put(p1.x, p1.y--, ctx->color, ctx->cur_buff) ;
			}
		}
	}
}