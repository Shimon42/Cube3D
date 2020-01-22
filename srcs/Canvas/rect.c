/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rect.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 17:15:35 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 22:57:55 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include <unistd.h>

void	draw_rect(int x, int y, int width, int height, int fill, t_ctx *ctx)
{
	static t_ctx *cur_ctx = NULL;
	int cur_h;

	if (fill == -1 || ctx)
		set_context(&cur_ctx, ctx);
	
	cur_h = 0;

	if (fill)
	{
		while (cur_h < height)
		{
			draw_line(new_point(x, y + cur_h), new_point(x + width, y + cur_h), cur_ctx);
			cur_h++;
		}
	}
	else
	{
		draw_line(new_point(x, y), new_point(x + width, y), cur_ctx);
		draw_line(new_point(x, y), new_point(x, y + height), cur_ctx);
		draw_line(new_point(x + width, y), new_point(x + width, y + height), cur_ctx);
		draw_line(new_point(x, y + height), new_point(x + width, y + height), cur_ctx);
	}
	return ;
}