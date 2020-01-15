/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:46:16 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 21:54:38 by siferrar    ###    #+. /#+    ###.fr     */
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

int				parse_map(t_map *map, char *line);
int				alloc_map(t_map *map);
#endif