/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:45:58 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:49:41 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		add_spr_to_list(t_spr_list *s_list, t_sprite *s)
{
	t_sprite	**ret;
	int			i;

	i = 0;
	ft_printf(YELO"Add spr to list\n");
	disp_sprite(s);
	ret = malloc((s_list->length + 1) * sizeof(t_sprite *));
	if (s_list->list != NULL)
		while (i < s_list->length)
		{
			ret[i] = s_list->list[i];
			i++;
		}
	ret[i] = s;
	free(s_list->list);
	s_list->list = ret;
	s_list->length++;
	ft_printf(GRN"Add spr to list OK\n"RST);
}

void		set_spr_texture(t_brain *b, t_sprite *s, int type)
{
	if (type == 2)
	{
		init_texture(b, "./assets/sprites/barrel.xpm", &s->model);
		init_texture(b, "./assets/sprites/barrel-shadow.xpm", &s->shadow);
	}
	else if (type == 3)
	{
		init_texture(b, "./assets/sprites/tree.xpm", &s->model);
		init_texture(b, "./assets/sprites/tree-shadow.xpm", &s->shadow);
	}
	else if (type == 4)
	{
		init_texture(b, "./assets/sprites/col2.xpm", &s->model);
		init_texture(b, "./assets/sprites/col2-shadow.xpm", &s->shadow);
	}
}

t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type)
{
	t_sprite	*s;
	t_brain		*b;

	ft_printf("Init Sprite\n");
	b = (t_brain *)m->brain;
	if (!(s = malloc(sizeof(t_sprite))))
		return (NULL);
	s->pos = pos;
	s->type = type;
	s->pos.x = pos.x * m->bloc_size + m->bloc_size / 2;
	s->pos.y = pos.y * m->bloc_size + m->bloc_size / 2;
	s->model = NULL;
	s->shadow = NULL;
	s->on_screen = 0;
	set_spr_texture(b, s, type);
	return (s);
}
