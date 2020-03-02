/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:46:16 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/02 07:53:24 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct	s_spr_list
{
	void		*s;
	void		*next;
	
}				t_spr_list;

typedef struct	s_detect
{
	float		dist;
	t_fpoint	hit;
	char		w_side_hit;
	char		from;
	void		**spr_on_path;
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
	float		scale;
	t_fpoint	disp;
	int			mini_map_width;
	int			sprites_count;
	void		*sprites;
	t_buff		*w_n;
	t_buff		*w_e;
	t_buff		*w_s;
	t_buff		*w_w;
	t_buff		*frame;
	void		*brain;
}				t_map;

int				init_map(t_ctx *ctx, void *brain);
int				parse_map(t_map **map, char *line);
int				alloc_map(t_map **map);
t_player_detect	*add_map_row(t_map *map, char *line);
int				**alloc_2d_tab(int width, int height);

#endif
