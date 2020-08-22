/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:42:08 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/22 13:36:57 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include "../../includes/cube3d.h"
#include <stdio.h>

void	free_ctx(t_ctx *c)
{
	if (c->mlx_ptr && c->buff && c->buff->img != NULL)
		mlx_destroy_image(c->mlx_ptr, c->buff->img);
	free(c->buff);
	if (c->win_ptr != NULL)
		mlx_destroy_window(c->mlx_ptr, c->win_ptr);
	ft_putstr("\033[0;33mFree MLX -> ");
	free_mlx(c->mlx_ptr);
	ft_putstr("OK\033[0;33m\n");
	check_n_free(c->mlx_ptr);
	check_n_free(c);
}

void	clear_ctx(int color, t_ctx *ctx)
{
	int oldcolor;

	oldcolor = 0;
	if (ctx->color >= 0)
		oldcolor = ctx->color;
	if (color >= 0)
		ctx->color = color;
	ctx->rect(new_point(0, 0), new_point(ctx->width, ctx->height), 1, ctx);
	ctx->color = oldcolor;
}

void	init_buff(t_ctx *ctx, t_buff **buff, int width, int height)
{
	(*buff) = malloc(sizeof(t_buff));
	if ((*buff) == NULL)
		exit_cube(NULL, 5, "Failed to malloc buff", 0);
	(*buff)->width = width;
	(*buff)->height = height;
	ft_printf(DCYAN"INIT BUFF %d x %d px\n"RST, width, height);
	(*buff)->img = NULL;
	(*buff)->addr = NULL;
	(*buff)->img = mlx_new_image(ctx->mlx_ptr, ctx->width, ctx->height);
	(*buff)->addr = mlx_get_data_addr((*buff)->img, &(*buff)->bits_per_pixel,
								&(*buff)->line_length,
								&(*buff)->endian);
	(*buff)->max_addr = (*buff)->line_length * (*buff)->height;
	(*buff)->offset = (*buff)->bits_per_pixel / 8;
	if ((*buff)->addr == NULL)
		exit_cube(NULL, 5, "Buff address not set", 0);
	if ((*buff)->img == NULL)
		exit_cube(NULL, 5, "Buff image not set", 0);
}

t_ctx	*new_ctx(int width, int height)
{
	t_ctx *ctx;

	ctx = malloc(sizeof(t_ctx));
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = 0;
	ctx->width = width;
	ctx->height = height;
	ctx->divided = new_fpoint(width / 2, height / 2);
	ctx->col_step = 0;
	ctx->line = &draw_line;
	ctx->rect = &draw_rect;
	ctx->circle = &draw_circle;
	ctx->text = &put_text;
	ctx->clear = &clear_ctx;
	ctx->color = 0;
	ctx->red_cross = 0;
	ctx->buff = NULL;
	return (ctx);
}
