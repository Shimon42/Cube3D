/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:46:16 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/10 15:08:25 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct      s_sprite
{
	t_fpoint        pos;
	int			    type;
	t_buff			*model;

	struct s_sprite	*next;
}				    t_sprite;

typedef struct	s_spr_list
{
	int			length;
	t_sprite	**list;
}				t_spr_list;

typedef struct	s_detect
{
	float		dist;
	t_fpoint	hit;
	char		w_side_hit;
	char		from;
	t_sprite	**spr_on_path;
}				t_detect;

typedef struct	s_player_detect
{
	int			pos_x;
	char		direction;
}				t_player_detect;

typedef	struct	s_map_line
{
	int length;
	int *line;
}				t_map_line;


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
	t_spr_list	*sprites;
	t_buff		*w_n;
	t_buff		*w_e;
	t_buff		*w_s;
	t_buff		*w_w;
	t_buff		*frame;
	t_buff		*skybox;
	void		*brain;
}				t_map;

int				init_map(t_ctx *ctx, void *brain);
int				parse_map(t_map **map, char *line);
int				alloc_map(t_map **map);
t_player_detect	*add_map_row(t_map *map, char *line);
int				**alloc_2d_tab(int width, int height);

#endif
