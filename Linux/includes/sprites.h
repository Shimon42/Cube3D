/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:51:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:46:01 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H
# define SPR_TRANSP 0x980088
# define EXT_EXT ".xpm"
# define EXT_SHD "-shadow.xpm"
# include "cube3d.h"

# include "cube3d.h"

t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type);
void		reorder_sprites(t_map *m);
void		add_spr_to_list(t_spr_list *s_list, t_sprite *s);
t_sprite	*get_sprite(t_map *m, t_fpoint p);

void		draw_sprite(void *brain, t_sprite *spr, float col);

void		disp_sprt_list(t_list *s_list);
void		disp_sprites(t_spr_list *s_list);
void		disp_sprite(t_sprite *spr);
#endif
