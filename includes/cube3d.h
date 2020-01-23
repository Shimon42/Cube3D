/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:30:44 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 19:11:41 by siferrar    ###    #+. /#+    ###.fr     */
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
# include "Libft/includes/libft.h"
# include "my_canvas.h"
# include "map.h"
# include "player.h"

typedef struct	s_player
{
	t_point		*pos;
	t_camera	*cam;
    double      angle;
    double      speed;
	void		(*move)(struct s_player *, t_ctx *);
}				t_player;

typedef struct	s_brain
{
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	
}				t_brain;

int				open_map(t_brain *b, char *map_path);
void			draw_minimap(t_brain *b, int x, int y, double scale);
void			draw_fullmap(t_brain *b, double scale);
void            draw_frame(t_brain *b, int x, int y, double scale);


int		init_player(t_brain *b, int pos_x);
void	move(struct s_player*, t_ctx *);


void    print_map_debug(char *line);
void	print_map_grid(t_map *map);

#endif