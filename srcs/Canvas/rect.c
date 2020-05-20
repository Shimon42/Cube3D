/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:15:35 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 15:28:15 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include <unistd.h>

void	fill_rect(t_point pos, t_point size, t_ctx *ctx)
{
	int cur_h;

	cur_h = 0;
	while (cur_h < size.y)
	{
		draw_line(new_point(pos.x, pos.y + cur_h),
						new_point(pos.x + size.x, pos.y + cur_h), ctx);
		cur_h++;
	}
}

void	draw_rect(t_point pos, t_point size, int fill, t_ctx *ctx)
{
	if (fill)
		fill_rect(pos, size, ctx);
	else
	{
		draw_line(new_point(pos.x, pos.y),
					new_point(pos.x + size.x, pos.y), ctx);
		draw_line(new_point(pos.x, pos.y),
					new_point(pos.x, pos.y + size.y), ctx);
		draw_line(new_point(pos.x + size.x, pos.y),
					new_point(pos.x + size.x, pos.y + size.y), ctx);
		draw_line(new_point(pos.x, pos.y + size.y),
					new_point(pos.x + size.x, pos.y + size.y), ctx);
	}
}
