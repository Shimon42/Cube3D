/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:30:44 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/24 08:20:02 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
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

typedef struct	s_brain
{
	int			inited;
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	int			*keys;
	
}				t_brain;

typedef struct	mlx_win_list_s
{
  void			*winid;
  void		*img_list;
  int			nb_flush;
  int			pixmgt;
  struct mlx_win_list_s	*next;
  int size_x;
  int size_y;
} mlx_win_list_t;

int				open_map(t_brain *b, char *map_path);
void			draw_minimap(t_brain *b, int x, int y, int width);
void			draw_fullmap(t_brain *b, double ease_val);
void            draw_frame(t_brain *b);
t_point			map_scaled(t_point *p, t_map *m);
t_fpoint		map_fscaled(t_fpoint *p, t_map *m);
int				get_grid(t_map *m, int x, int y, int need_rescale);
t_point			to_grid(int x, int y, t_map *m);
void			point_on_map(t_brain *b, int x, int y, int color);
void	line_on_map(t_brain *b, t_point p1, t_point p2);
void	draw_fov_map(t_brain *b, t_ctx *c);

t_fpoint		to_fpoint(t_point *p);
double to_360(double angle);
double			calc_dist(t_point p1, t_point p2);
double			calc_fdist(t_fpoint p1, t_fpoint p2);

int				init_player(t_brain *b, int pos_x, char angle);
void			move(struct s_player*, int dir);
void			rotate(struct s_player *p, double angle);
void			draw_player(struct s_player *p, t_ctx *ctx);
void			side_move(struct s_player *p, int dir);
void			jump(t_player *p, double speed);

t_fpoint		closest_grid_h(t_point *p, t_map *m, double angle);
t_fpoint		closest_grid_v(t_point *p, t_map *m, double angle);
t_fpoint		closest_wall_h(t_brain *b, t_point *p, double angle);
t_fpoint		closest_wall_v(t_brain *b, t_point *p, double angle);
t_detect		dist_to_wall(t_brain *b, t_point *p, double angle);
void			draw_walls(t_brain *b, t_ctx *c);
void draw_col(t_brain *b, double w_height, double cur_col, t_detect w);

int		pixel_get(t_buff *img, int x, int y);
void			draw_ray(t_player *p, t_map *m, double angle);
void			draw_minimap_rays(t_brain *b, t_point disp);

/* ---------------- DEBUG ---------*/
void    		print_map_debug(char *line);
void			print_map_grid(t_map *map);
void			disp_map_s(t_map *m);
void			disp_buff(t_buff *b);
void    		print_player_debug(t_brain *b);
void			disp_brain(t_brain *b);

#endif