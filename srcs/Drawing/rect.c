/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rect.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 17:15:35 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 17:38:13 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	draw_rect(t_ctx *ctx, int x, int y, int width, int height)
{
	int cur_h;

	cur_h = 0;
	while (cur_h < height)
	{
		draw_line(ctx, new_point(x, y + cur_h), new_point(x + width, y + cur_h));
		cur_h++;
	}
}