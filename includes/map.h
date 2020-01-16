/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:46:16 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 21:49:39 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct	s_map
{
	int			**grid;
	int			width;
	int			height;
	int			bloc_size;		
	double		scale;
}				t_map;

int				parse_map(t_map **map, char *line);
int				alloc_map(t_map **map);
int				add_map_row(t_map **map, char *line);
#endif