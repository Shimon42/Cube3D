/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:42:08 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/15 17:54:17 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/my_canvas.h"
#include "../../includes/cube3d.h"

void	clear_ctx(int color, t_ctx *ctx)
{
	int oldColor;

	oldColor = 0;
	if (ctx->color >= 0)
		oldColor = ctx->color;
	if (color >= 0)
		ctx->color = color;
	ctx->rect(0, 0, ctx->width, ctx->height, 1, ctx);
	ctx->color = oldColor;
}

void	init_ctx_funcs(t_ctx *ctx)
{
	ctx->line(new_point(-1, -1), new_point(-1, -1), ctx);
	ctx->rect(0, 0, 0, 0, -1, ctx);
	ctx->circle(0, 0, 0, -1, ctx);
}

void	set_context(t_ctx **cur, t_ctx **new_ctx, char *name)
{
	write(1, "Setting context for ", 20);
	ft_putstr(name);
	ft_putchar('\n');
	if (*cur == NULL || (*new_ctx && *cur != *new_ctx))
	{
		if (*new_ctx)
		{
			*cur = *new_ctx;
			write(1, "Context SET\n", 12);
			return ;
		}
		else
		{
			write(1, "\033[0;31mCTX NOT SET\n", 19);
			exit(0);
		}
	}
	else
		write(1, "Context Already SET\n", 20);
}

void init_buff(t_ctx * ctx, t_buff **buff, int width, int height)
{
	(*buff) = malloc(sizeof(t_buff));
	if ((*buff) == NULL)
	{
		ft_putstr(RED"BUFF NOT SET"RST);
		exit(3);
	}
	(*buff)->width = width;
	(*buff)->height = height;
	dprintf(1, DCYAN"INIT BUFF %d x %d px\n"RST, width, height);
	(*buff)->img = NULL;
	(*buff)->addr = NULL;
	(*buff)->img = mlx_new_image(ctx->mlx_ptr, ctx->width, ctx->height);
	(*buff)->addr = mlx_get_data_addr((*buff)->img, &(*buff)->bits_per_pixel, &(*buff)->line_length,
                                 &(*buff)->endian);
	(*buff)->max_addr = (*buff)->line_length * (*buff)->height;
	(*buff)->offset = (*buff)->bits_per_pixel / 8;
	if ((*buff)->addr == NULL)
	{
		ft_putstr(RED"BUFF NOT SET"RST);
		exit(5);
	}
	if ((*buff)->img == NULL)
	{
		ft_putstr(RED"BUFF NOT SET"RST);
		exit(4);
	}
}

t_ctx	*new_ctx(int width, int height)
{
	t_ctx *ctx;

	ctx = malloc(sizeof(t_ctx));
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = 0;
	ctx->width = width;
	ctx->height = height;
	ctx->line = &draw_line;
	ctx->rect = &draw_rect;
	ctx->circle = &draw_circle;
	ctx->text = &put_text;
	ctx->clear = &clear_ctx;
	return(ctx);
}

void pixel_put(int x, int y, t_ctx *ctx)
{
	mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color);
}

void            pixel_put_buff(int x, int y, int color, t_buff *buff)
{
    char    *dst;
	int addr_index;

	addr_index = (y * buff->line_length + x * buff->offset);
	if(addr_index >= 0 && addr_index < buff->max_addr)
	{
    	dst = buff->addr + addr_index;
		*(unsigned int*)dst = color;
	}
	//dprintf(1, "OK\n");
}

int		pixel_get(t_buff *img, int x, int y)
{
    char    *dst;
	int addr_index;
	int *color;
	
	addr_index = (y * img->line_length + x * img->offset);
	if(addr_index >= 0 && addr_index < img->max_addr)
	{
    	dst = img->addr + addr_index;
		color = (int*)(dst);
		return(*color);
	}
	return (-1);
}

