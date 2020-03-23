/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_canvas.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:33:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/23 10:22:00 by siferrar         ###   ########lyon.fr   */
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
	void		(*line)(t_fpoint, t_fpoint, struct s_ctx *);
	void		(*rect)(int, int, int, int, int, struct s_ctx *);
	void		(*circle)(float, float, int, int, struct s_ctx *);
	void		(*text)(char *, int, int, struct s_ctx *);
	void		(*clear)(int, struct s_ctx *);
}				t_ctx;

t_ctx			*new_ctx(int width, int height);
void			init_buff(t_ctx *ctx, t_buff **buff, int width, int height);
void			pixel_put(int x, int y, int color, t_buff *buff);
int				pixel_get(t_buff *img, int x, int y);
void			draw_line(t_fpoint p1, t_fpoint p2, t_ctx *ctx);
void			draw_rect(int x, int y,
						int width, int height, int fill, t_ctx *ctx);
void			draw_circle(float c_x, float c_y,
						int ray, int fill, t_ctx *ctx);
void			put_text(char *str, int x, int y, t_ctx *ctx);
void			clear_ctx(int color, t_ctx *ctx);

t_fpoint		new_point(int x, int y);
void			disp_point(t_fpoint *p);

#endif
