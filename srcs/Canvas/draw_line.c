/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:20:40 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/08 17:58:31 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

int		first_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->x;
	diff->x = ret * 2;
	diff->y *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (++p1->x == p2->x)
			break ;
		if ((ret -= diff->y) < 0)
		{
			p1->y++;
			ret += diff->x;
		}
	}
	return (ret);
}

int		second_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->y;
	diff->y = ret * 2;
	diff->x *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (++p1->y == p2->y)
			break ;
		if ((ret -= diff->x) < 0)
		{
			p1->x++;
			ret += diff->y;
		}
	}
	return (ret);
}

void	calc_first_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;

	if (diff.x >= diff.y)
	{
		e = first_octant(ctx, &p1, &p2, &diff);
	}
	else
	{
		e = second_octant(ctx, &p1, &p2, &diff);
	}
}

int		third_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->y;
	diff->y = ret * 2;
	diff->x *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (++p1->y == p2->y)
			break ;
		if ((ret += diff->x) <= 0)
		{
			p1->x--;
			ret += diff->y;
		}
	}
	return (ret);
}

int		fourth_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->x;
	diff->x = ret * 2;
	diff->y *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (--p1->x == p2->x)
			break ;
		if ((ret += diff->y) >= 0)
		{
			p1->y++;
			ret += diff->x;
		}
	}
	return (ret);
}

void	calc_second_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;

	if (-diff.x >= diff.y)
	{
		e = fourth_octant(ctx, &p1, &p2, &diff);
	}
	else
	{
		e = third_octant(ctx, &p1, &p2, &diff);
	}
}

int		fifth_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->x;
	diff->x = ret * 2;
	diff->y *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (--p1->x == p2->x)
			break ;
		if ((ret -= diff->y) >= 0)
		{
			p1->y--;
			ret += diff->x;
		}
	}
	return (ret);
}

int		sixth_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->y;
	diff->y = ret * 2;
	diff->x *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (--p1->y == p2->y)
			break ;
		if ((ret -= diff->x) >= 0)
		{
			p1->x--;
			ret += diff->y;
		}
	}
	return (ret);
}

void	calc_third_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int		e;

	if (diff.x <= diff.y)
	{
		e = fifth_octant(ctx, &p1, &p2, &diff);
	}
	else
	{
		e = sixth_octant(ctx, &p1, &p2, &diff);
	}
}

int		seventh_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->y;
	diff->y = ret * 2;
	diff->x *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (--p1->y == p2->y)
			break ;
		if ((ret += diff->x) > 0)
		{
			p1->x++;
			ret += diff->y;
		}
	}
	return (ret);
}

int		eigth_octant(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
{
	int ret;

	ret = diff->x;
	diff->x = ret * 2;
	diff->y *= 2;
	while (1)
	{
		pixel_put(p1->x, p1->y, ctx->color, ctx->cur_buff);
		if (++p1->x == p2->x)
			break ;
		if ((ret += diff->y) < 0)
		{
			p1->y--;
			ret += diff->x;
		}
	}
	return (ret);
}

void	calc_fourth_quad(t_ctx *ctx, t_fpoint p1, t_fpoint p2, t_fpoint diff)
{
	int	e;

	if (diff.x >= -diff.y)
	{
		e = eigth_octant(ctx, &p1, &p2, &diff);
	}
	else
	{
		e = seventh_octant(ctx, &p1, &p2, &diff);
	}
}

void	calc_quads(t_ctx *ctx, t_fpoint *p1, t_fpoint *p2, t_fpoint *diff)
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
	else
	{
		if ((diff->y = p2->y - p1->y) != 0)
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
}

void	draw_line(t_fpoint p1, t_fpoint p2, t_ctx *ctx)
{
	t_fpoint diff;

	diff = new_point(0, 0);
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
