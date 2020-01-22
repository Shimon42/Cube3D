/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   brain.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 21:47:46 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 17:56:10 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include "cube3d.h"

typedef struct	s_brain
{
	t_ctx		*ctx;
	t_map		*map;
	
}				t_brain;

int				open_map(t_brain *b, char *map_path);
void			draw_minimap(t_brain *b, int x, int y, double scale);
void            draw_frame(t_brain *b, int x, int y, double scale);
#endif