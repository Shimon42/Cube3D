/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rect.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 17:15:35 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 22:15:43 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include <unistd.h>

void	draw_rect(int x, int y, int width, int height, int fill, t_ctx *ctx)
{
	int cur_h;
	
	cur_h = 0;
	//printf("rect height: %d\nrect width: %d\n", width, height);
	if (fill)
	{
		while (cur_h < height)
		{
			draw_line(new_point(x, y + cur_h), new_point(x + width - 1, y + cur_h), ctx);
			cur_h++;
		}
	}
	else
	{
		draw_line(new_point(x, y), new_point(x + width - 1, y), ctx);
		draw_line(new_point(x, y), new_point(x, y + height  - 1), ctx);
		draw_line(new_point(x + width - 1, y), new_point(x + width - 1, y + height - 1), ctx);
		draw_line(new_point(x, y + height - 1), new_point(x + width - 1, y + height - 1), ctx);
	}
	return ;
}