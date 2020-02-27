/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:51:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/27 09:26:55 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifndef SPRITES_H
# define SPRITES_H

typedef struct      s_sprite
{
	t_fpoint        pos;
	int			    type;

	struct s_sprite	*next;
}				    t_sprite;

t_sprite	*init_sprite(t_fpoint pos, int type);
void		add_sprite(t_map *m, int posX, int type);
void		reorder_sprites(t_map *m);
void		disp_sprites(t_sprite *s);

#endif