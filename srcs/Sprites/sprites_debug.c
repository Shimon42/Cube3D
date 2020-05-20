/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:45:04 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 14:57:02 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		disp_sprites(t_spr_list *s_list)
{
	int			i;
	t_sprite	*s;

	i = 0;
	ft_putstr(PINK);
	if (s_list->list != NULL)
	{
		ft_printf("%d sprites in list\n", s_list->length);
		while (i < s_list->length)
		{
			disp_sprite(s_list->list[i]);
			i++;
		}
		ft_printf("End of loop\n");
	}
	else
		ft_printf("No sprites in list\n");
	ft_putstr(RST);
}

void		disp_sprite(t_sprite *s)
{
	ft_printf("Sprite of type %d\n", s->type);
	disp_point(s->pos);
}
