/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:51:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/02 08:59:51 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifndef SPRITES_H
# define SPRITES_H

typedef struct      s_sprite
{
	t_fpoint        pos;
	int			    type;
	t_buff			*model;

	struct s_sprite	*next;
}				    t_sprite;

t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type);
void		add_sprite(t_map *m, int posX, int type);
void		reorder_sprites(t_map *m);
void		add_spr_to_list(t_spr_list *s_list, t_sprite *s);
t_sprite	*get_sprite(t_map *m, t_fpoint p);

void	draw_sprite(void *brain, t_sprite *s, float col, int y);

void		disp_sprt_list(t_list *s_list);
void		disp_sprites(t_sprite *s);
void	disp_sprite(void *spr);
#endif