/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   my_canvas.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 17:33:03 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 19:30:05 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MY_CANVAS_H
# define MY_CANVAS_H
# include <stdlib.h>
# include <stdio.h>

#include "MiniLib/mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;

}				t_point;

typedef struct	s_ctx
{
	int			width;
	int			height;
	int			color;
	int			line_width;
	void		*mlx_ptr;
	void		*win_ptr;
	void		(*line)(struct s_ctx *, t_point, t_point);
	void		(*rect)(struct s_ctx *, int, int, int, int, int);
	void		(*clear)(struct s_ctx *, int);
}				t_ctx;

t_ctx			*new_ctx(int width, int height);

void			pixel_put(t_ctx *ctx, int x, int y);
void			draw_line(t_ctx *ctx, t_point p1, t_point p2);
void			draw_rect(t_ctx *ctx, int x, int y, int width, int height, int fill);
void			clear_ctx(t_ctx *ctx, int color);

t_point	new_point(int x, int y);
void			disp_point(t_point p);

#endif