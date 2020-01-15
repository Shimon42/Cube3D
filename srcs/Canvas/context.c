/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   context.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 18:42:08 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 19:25:07 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	clear_ctx(t_ctx *ctx, int color)
{
	if (color)
		ctx->color = color;
	ctx->rect(ctx, 0, 0, ctx->width, ctx->height, 1);
}

t_ctx	*new_ctx(int width, int height)
{
	t_ctx *ctx;

	ctx = malloc(sizeof(t_ctx));
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = NULL;
	ctx->width = width;
	ctx->height = height;
	ctx->line = &draw_line;
	ctx->rect = &draw_rect;
	ctx->clear = &clear_ctx;
	return(ctx);
}

void pixel_put(t_ctx *ctx, int x, int y)
{
	mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color);
}