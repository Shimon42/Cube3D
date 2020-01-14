/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:30:44 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 21:31:51 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "MiniLib/mlx.h"
# include "../debug.h"
# include "points.h"
# include "Libft/includes/libft.h"

typedef struct	s_ctx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			color;

}				t_ctx;

typedef struct	s_brain
{
	t_ctx		*ctx;
}				t_brain;

void			pixel_put(t_ctx *ctx, int x, int y);
void			draw_line(t_ctx *ctx, t_point p1, t_point p2);
void			draw_rect(t_ctx *ctx, int x, int y, int width, int height);
int				parse_map(t_brain *b, char *map_path);
#endif