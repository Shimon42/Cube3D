/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rect.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 17:15:35 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 20:00:22 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	draw_rect(t_ctx *ctx, int x, int y, int width, int height, int fill)
{
	int cur_h;

	cur_h = 0;

	if (fill)
	{
		while (cur_h < height)
		{
			draw_line(ctx, new_point(x, y + cur_h), new_point(x + width, y + cur_h));
			cur_h++;
		}
	}
	else
	{
		draw_line(ctx, new_point(x, y), new_point(x + width, y));
		draw_line(ctx, new_point(x, y), new_point(x, y + height));
		draw_line(ctx, new_point(x + width, y), new_point(x + width, y + height));
		draw_line(ctx, new_point(x, y + height), new_point(x + width, y + height));
	}
	return ;
}