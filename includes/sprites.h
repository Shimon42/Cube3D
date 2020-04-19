/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:51:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/19 02:20:00 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifndef SPRITES_H
# define SPRITES_H
# define SPR_TRANSP 0x980088

t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type);
void		add_sprite(t_map *m, int posX, int type);
void		sort_sprites(void *brain, t_spr_list *lst_sprt);
void		swap_sprite(t_spr_list *lst_sprt, int num1, int num2);
void		add_spr_to_list(t_spr_list *s_list, t_sprite *s);

void	draw_sprite(void *brain, t_sprite *spr, float col);

void		disp_sprt_list(t_list *s_list);
void		disp_sprites(t_spr_list *s_list);
void		disp_sprite(t_sprite *spr);
#endif