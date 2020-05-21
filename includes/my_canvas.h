/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_canvas.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:33:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:45:30 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_CANVAS_H
# define MY_CANVAS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "MiniLib/mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_fpoint
{
	float		x;
	float		y;
}				t_fpoint;

typedef struct	s_buff {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			offset;
	int			max_addr;
	double		ratio;
	int			initied;
}				t_buff;

typedef struct	s_ctx
{
	int			width;
	int			height;
	int			color;
	int			line_width;
	void		*mlx_ptr;
	void		*win_ptr;
	t_buff		*buff;
	t_buff		*cur_buff;
	t_fpoint	divided;
	float		col_step;
	void		(*line)(t_point, t_point, struct s_ctx *);
	void		(*rect)(t_point, t_point, int, struct s_ctx *);
	void		(*circle)(t_fpoint, int, int, struct s_ctx *);
	void		(*text)(char *, int, int, struct s_ctx *);
	void		(*clear)(int, struct s_ctx *);
}				t_ctx;

t_ctx			*new_ctx(int width, int height);
void			init_buff(t_ctx *ctx, t_buff **buff, int width, int height);
void			pixel_put(int x, int y, int color, t_buff *buff);
int				pixel_get(t_buff *img, int x, int y);
void			draw_line(t_point p1, t_point p2, t_ctx *ctx);
void			draw_rect(t_point pos, t_point size, int fill, t_ctx *ctx);
void			draw_circle(t_fpoint pos,
						int ray, int fill, t_ctx *ctx);
void			put_text(char *str, int x, int y, t_ctx *ctx);
void			clear_ctx(int color, t_ctx *ctx);

t_point			new_point(int x, int y);
t_fpoint		new_fpoint(float x, float y);
void			disp_point(t_fpoint p);

void			calc_first_quad(t_ctx *ctx,
					t_point p1, t_point p2, t_fpoint diff);
void			calc_second_quad(t_ctx *ctx,
					t_point p1, t_point p2, t_fpoint diff);
void			calc_third_quad(t_ctx *ctx,
					t_point p1, t_point p2, t_fpoint diff);
void			calc_fourth_quad(t_ctx *ctx,
					t_point p1, t_point p2, t_fpoint diff);

#endif
