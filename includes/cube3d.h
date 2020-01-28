/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:30:44 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 22:57:24 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H
# define PI 3.14159265359
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "MiniLib/mlx.h"
# include "../debug.h"
# include "Libft/includes/libft.h"
# include "my_canvas.h"
# include "map.h"
# include "player.h"
# include "MiniLib/X.h"

typedef struct	s_camera
{
	t_point		*pos;
	double		height;
	double		fov;
}				t_camera;

typedef struct	s_player
{
	int			inited;
	t_point		*pos;
	t_camera	*cam;
    double      angle;
    double      rot_speed;
    double      speed;
	t_ctx		*ctx;
	void		(*rot)(struct s_player *, int);
	void		(*move)(struct s_player *, int);
	void		(*draw)(struct s_player *, t_ctx *);
}				t_player;

typedef struct	s_brain
{
	int			inited;
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	int			*keys;
	
}				t_brain;

int				open_map(t_brain *b, char *map_path);
void			draw_minimap(t_brain *b, int x, int y, double scale);
void			draw_fullmap(t_brain *b, double scale);
void            draw_frame(t_brain *b, int x, int y, double scale);


int		init_player(t_brain *b, int pos_x);
void	move(struct s_player*, int dir);
void	rotate(struct s_player *p, int dir);
void	draw_player(struct s_player *p, t_ctx *ctx);

/* ---------------- DEBUG ---------*/
void    print_map_debug(char *line);
void	print_map_grid(t_map *map);
void	disp_map_s(t_map *m);
void	disp_buff(t_buff *b);
#endif