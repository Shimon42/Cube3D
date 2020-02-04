/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:30:44 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 22:52:54 by siferrar    ###    #+. /#+    ###.fr     */
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
# include "Libft/includes/libft.h"
# include "my_canvas.h"
# include "map.h"
# include "player.h"
# include "MiniLib/X.h"
# include "../debug.h"
# include "../debug_defines.h"

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
	void		*brain;
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
void			draw_minimap(t_brain *b, int x, int y, int width);
void			draw_fullmap(t_brain *b, double ease_val);
void            draw_frame(t_brain *b, int x, int y, double scale);
t_point			map_scaled(t_point *p, t_map *m);
int				get_grid(t_map *m, int x, int y);
t_point			to_grid(t_point *p, t_map *m);

int		init_player(t_brain *b, int pos_x);
void	move(struct s_player*, int dir);
void	rotate(struct s_player *p, int dir);
void	draw_player(struct s_player *p, t_ctx *ctx);

t_point			closest_grid_h(t_point *p, t_map *m, double angle);
t_point			closest_grid_v(t_point *p, t_map *m, double angle);

void draw_ray(t_player *p, t_map *m, double angle);
void	draw_minimap_rays(t_brain *b, t_point disp);

/* ---------------- DEBUG ---------*/
void    print_map_debug(char *line);
void	print_map_grid(t_map *map);
void	disp_map_s(t_map *m);
void	disp_buff(t_buff *b);
void    print_player_debug(t_brain *b);
void disp_brain(t_brain *b);

#endif