/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/27 09:39:37 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_sprite   *init_sprite(t_fpoint pos, int type)
{
	t_sprite *s;

	s = malloc(sizeof(t_sprite));
	s->pos = pos;
	s->type = type;
	s->next = NULL;
	return (s);
}

void    add_sprite(t_map *m, int posX, int type)
{
	t_sprite *list;
	t_sprite *tmp;
	t_sprite *s;

	dprintf(1, "Add sprite at posX: %d - posY: %d\n", posX, m->height);
	s = init_sprite(new_point(posX, m->height), type);
	tmp = NULL;
	list = (t_sprite *)m->sprites;
	if (list == NULL)
		list = s;
	else
	{
		tmp = list;
		while (tmp != NULL)
		{
			if (tmp->next == NULL)
				tmp->next = s;
			tmp = tmp->next;
		}
		
	}
	disp_sprites(list);
}

void	disp_sprites(t_sprite *s)
{
	t_sprite	*cur;
	int			i;

	i = 0;
	if (s != NULL)
	{
		cur = s;
		while (cur != NULL)
		{
			dprintf(1, "Sprite %d\n", i);
			disp_point(&(cur->pos));
			cur = cur->next;
			i++;
		}
	}
}

void    reorder_sprites(t_map *m)
{
	
}