/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:46:16 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 15:07:41 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct	s_detect
{
	double		dist;
	char		w_side_hit;
}				t_detect;

typedef struct	s_map
{
	char		*grid;
	int			width;
	int			height;
	int			px_width;
	int			px_height;
	int			bloc_size;		
	double		scale;
	int			mini_map_width;
	int			w_n;
	int			w_e;
	int			w_s;
	int			w_w;
}				t_map;

int				init_map(t_map **map);
int				parse_map(t_map **map, char *line);
int				alloc_map(t_map **map);
int				add_map_row(t_map *map, char *line);
int				**alloc_2d_tab(int width, int height);

#endif