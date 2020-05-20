/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:46:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 14:57:15 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		copy_sprite(t_sprite *from, t_sprite *to)
{
	to->dist = from->dist;
	to->pos = from->pos;
	to->model = from->model;
	to->shadow = from->shadow;
	to->type = from->type;
}

void		swap_sprite(t_spr_list *lst_sprt, int num1, int num2)
{
	t_sprite	temp;
	t_sprite	*spr_a;
	t_sprite	*spr_b;

	if ((num1 < lst_sprt->length)
		&& (num2 < lst_sprt->length) && (num1 != num2))
	{
		spr_a = lst_sprt->list[num1];
		spr_b = lst_sprt->list[num2];
		copy_sprite(spr_a, &temp);
		copy_sprite(spr_b, spr_a);
		copy_sprite(&temp, spr_b);
	}
}

void		sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt)
{
	float	dist1;
	float	dist2;
	int		i;
	int		j;

	i = 0;
	while (i < lst_sprt->length)
	{
		j = i;
		while (j < lst_sprt->length)
		{
			dist1 = calc_dist(*pos, lst_sprt->list[i]->pos);
			dist2 = calc_dist(*pos, lst_sprt->list[j]->pos);
			lst_sprt->list[i]->dist = dist1;
			lst_sprt->list[j]->dist = dist2;
			if (dist1 < dist2)
				swap_sprite(lst_sprt, i, j);
			j++;
		}
		i++;
	}
}

void		update_sprite(t_brain *b)
{
	int i;

	i = 0;
	sort_sprites(b->player->pos, b->map->sprites);
	while (i < b->map->sprites->length)
	{
		draw_sprite(b, b->map->sprites->list[i], 0);
		i++;
	}
}
