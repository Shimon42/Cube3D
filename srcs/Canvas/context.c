/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   context.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 18:42:08 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 22:58:40 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	clear_ctx(int color, t_ctx *ctx)
{
	if (color)
		ctx->color = color;
	ctx->rect(0, 0, ctx->width, ctx->height, 1, ctx);
}

void	init_ctx_funcs(t_ctx *ctx)
{
	ctx->line(new_point(-1, -1), new_point(-1, -1), ctx);
	ctx->rect(0, 0, 0, 0, 0, ctx);
}

void	set_context(t_ctx **cur, t_ctx *new_ctx)
{
	if (cur == NULL || new_ctx)
	{
		if (new_ctx)
			*cur = new_ctx;
		else
		{
			write(1, "\033[0;31mCTX NOT SET\n", 19);
			exit(0);
		}
	}
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
	init_ctx_funcs(ctx);
	return(ctx);
}

void pixel_put(int x, int y, t_ctx *ctx)
{
	mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color);
}