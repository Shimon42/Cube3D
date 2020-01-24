/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   my_canvas.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 17:33:03 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 16:01:51 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MY_CANVAS_H
# define MY_CANVAS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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
	void		(*line)(t_point, t_point, struct s_ctx *);
	void		(*rect)(int, int, int, int, int, struct s_ctx *);
	void		(*circle)(double, double, int, int, struct s_ctx *);
	void		(*clear)(int, struct s_ctx *);
}				t_ctx;

t_ctx			*new_ctx(int width, int height);
void			set_context(t_ctx **cur, t_ctx **new_ctx, char *name);
void			pixel_put(int x, int y, t_ctx *ctx);
void			draw_line(t_point p1, t_point p2, t_ctx *ctx);
void			draw_rect(int x, int y, int width, int height, int fill, t_ctx *ctx);
void			draw_circle(double c_x, double c_y, int ray, int fill, t_ctx *ctx);
void			clear_ctx(int color, t_ctx *ctx);

t_point	new_point(int x, int y);
void			disp_point(t_point *p);

#endif