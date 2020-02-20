/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:46:16 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/20 16:47:03 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct	s_detect
{
	double		dist;
	t_fpoint	hit;
	char		w_side_hit;
	char		from;
}				t_detect;

typedef struct	s_player_detect
{
	int			pos_x;
	char		direction;
}				t_player_detect;

typedef struct	s_map
{
	char		*grid;
	int			width;
	int			height;
	int			px_width;
	int			px_height;
	int			bloc_size;		
	double		scale;
	t_point		disp;
	int			mini_map_width;
	t_buff		*w_n;
	t_buff		*w_e;
	t_buff		*w_s;
	t_buff		*w_w;
	t_buff		*frame;
}				t_map;

int				init_map(t_ctx *ctx, t_map **map);
int				parse_map(t_map **map, char *line);
int				alloc_map(t_map **map);
t_player_detect		*add_map_row(t_map *map, char *line);
int				**alloc_2d_tab(int width, int height);

#endif