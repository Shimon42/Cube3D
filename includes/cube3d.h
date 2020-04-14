/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:30:44 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/13 16:45:32 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <pthread.h>
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
# include "sprites.h" 
# include "player.h"
# include "MiniLib/X.h"
# include "../debug/debug.h"
# include "../debug/debug_defines.h"

/*
** --- Brain
*/

typedef struct	s_brain
{
	int			inited;
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	int			*keys;
}				t_brain;

typedef struct	s_type
{
	int			height;
	int			width;
	int			valid;
	int			res[3];
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		*f;
	char		*c;
}				t_type;

void			exit_cube(t_brain *brain, int error_code, char *msg, int init);
void			meditate(t_brain *b);
/*
** --- Copy of mlx structure to gest sizes > screen size
*/

typedef struct	s_mlx_win_list
{
	void		*winid;
	void		*img_list;
	int			nb_flush;
	int			pixmgt;
	void		*next;
	int			size_x;
	int			size_y;
}				t_mlx_win_list;

/*
** --- Map and Minimap
*/

int				open_map(t_brain *b, char *map_path, t_type *map);
void			draw_minimap(t_brain *b, int x, int y, int width);
void			draw_fullmap(t_brain *b, float ease_val);
void			draw_frame(t_brain *b);
t_fpoint		map_scaled(t_fpoint *p, t_map *m);
t_fpoint		map_fscaled(t_fpoint *p, t_map *m);
int				get_grid(t_map *m, int x, int y, int need_rescale);
t_fpoint		to_grid(int x, int y, t_map *m);
void			point_on_map(t_brain *b, int x, int y, int color);
void			line_on_map(t_brain *b, t_fpoint p1, t_fpoint p2);
void			draw_fov_map(t_brain *b, t_ctx *c);
void			draw_ray(t_player *p, t_map *m, float angle);
void			draw_minimap_rays(t_brain *b, t_fpoint disp);
void			init_texture(t_brain *b, char *path, t_buff **t);

/*
** --- Utils
*/

t_fpoint		to_fpoint(t_fpoint *p);
float			to_360(float angle);
float			calc_dist(t_fpoint p1, t_fpoint p2);
float			calc_dist(t_fpoint p1, t_fpoint p2);

/*
** --- Player
*/

int				init_player(t_brain *b, int pos_x, char angle);
void			move(struct s_player *p, int dir);
void			rotate(struct s_player *p, float angle);
void			side_move(struct s_player *p, int dir);
void			jump(t_player *p, float speed);

/*
** --- Controls
*/

int				is_key_pressed(t_brain *b, int key);
int				add_key_pressed(t_brain *b, int key);
int				del_key_pressed(t_brain *b, int key);
int				key_press(int key, void *param);
int				key_release(int key, void *param);

/*
** --- RayCasting
*/

void	draw_sky(t_brain *b, t_ctx *c, double col, double end);

t_fpoint		closest_grid_h(t_fpoint *p, t_map *m, float angle);
t_fpoint		closest_grid_v(t_fpoint *p, t_map *m, float angle);
t_detect		closest_wall_h(t_brain *b, t_fpoint *p, float angle);
t_detect		closest_wall_v(t_brain *b, t_fpoint *p, float angle);
t_detect		dist_to_wall(t_brain *b, t_fpoint *p, float angle);
void			draw_walls(t_brain *b, t_ctx *c);
void			draw_col(t_brain *b, float w_height,
				float cur_col, t_detect w);

/*
** --- FloorCasting
*/

void draw_floor(t_brain *b, t_ctx *c, double cur_angle, int w_start, double col);

/*
** --- DEBUG FUNCTIONS
*/

void			print_map_debug(t_map_line *line);
void			print_map_grid(t_map *map);
void			disp_map_s(t_map *m);
void			disp_buff(t_buff *b);
void			print_player_debug(t_brain *b);
void			disp_brain(t_brain *b);


/*
** --- Parsing
*/

void			ft_getmap_flag(int fd, t_type *map);
void			ft_getmap_values(char *line, t_type *map);
void			ft_flag_str(char *str, char **target, t_type *map);
void			ft_flag_color(char *str, int *target, t_type *map);
void			ft_flag_res(char *str, int *target, t_type *map);
char			*ft_str_search(char *str, char *chrs);
void			ft_check_struct(t_type *map);

/*
** --- Utilities
*/

int				ft_strmultichr(char *str, char *chrlst);
int				ft_ext_check(char *str, char *end);
void			ft_init_t_type(t_type *map);
void			exit_flag(int err_num, char *str, t_type *map);
void			update_sprite(t_brain *b);
void    		sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt);

#endif
