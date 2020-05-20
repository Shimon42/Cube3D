/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_fourth_quad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 11:44:01 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:45:11 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/my_canvas.h"

int		seventh_octant(t_ctx *ctx, t_point *p1, t_point *p2, t_fpoint *diff)
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

int		eigth_octant(t_ctx *ctx, t_point *p1, t_point *p2, t_fpoint *diff)
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

void	calc_fourth_quad(t_ctx *ctx, t_point p1, t_point p2, t_fpoint diff)
{
	int	e;

	if (diff.x >= -diff.y)
		e = eigth_octant(ctx, &p1, &p2, &diff);
	else
		e = seventh_octant(ctx, &p1, &p2, &diff);
}
