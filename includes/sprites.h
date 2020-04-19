/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:51:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/19 01:32:58 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifndef SPRITES_H
# define SPRITES_H
# define SPR_TRANSP 0x980088

t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type);
void		add_sprite(t_map *m, int posX, int type);
void		reorder_sprites(t_map *m);
void		add_spr_to_list(t_spr_list *s_list, t_sprite *s);
t_sprite	*get_sprite(t_map *m, t_fpoint p);

void	draw_sprite(void *brain, t_sprite *spr, float col);

void		disp_sprt_list(t_list *s_list);
void		disp_sprites(t_spr_list *s_list);
void		disp_sprite(t_sprite *spr);
#endif