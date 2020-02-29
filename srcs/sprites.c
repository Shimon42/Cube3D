/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/29 21:01:42 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_sprite   *init_sprite(t_map *m, t_fpoint pos, int type)
{
	t_sprite	*s;
	t_brain		*b;

	b = (t_brain *)m->brain;
	if (!(s = malloc(sizeof(t_sprite))))
		return (NULL);
	s->pos = pos;
	s->pos.x = pos.x * m->bloc_size;
	s->pos.y = pos.y * m->bloc_size;
	s->model = NULL;
	init_texture(b, "./assets/sprites/barrel.xpm", &s->model);
	s->type = 1;
	s->next = NULL;
	return (s);
}

int		compare(t_fpoint p1, t_fpoint p2, int range)
{
	if (p1.x >= p2.x - range && p1.x <= p2.x + range && p1.y >= p2.y - range && p1.y <= p2.y + range)
		return (1);
	else
		return (0);
}

t_sprite *get_sprite(t_map *m, t_fpoint p)
{
	t_sprite **ptr;
	t_fpoint in_grid;

	dprintf(1, "Getting sprite\n");

	ptr = &m->sprites;
	while (*ptr != NULL)
	{
		dprintf(1, "Check Sprites x:%f y:%f  VS x:%f y:%f \n", (*ptr)->pos.x, (*ptr)->pos.y, p.x, p.y);
		if (compare((*ptr)->pos, p, m->bloc_size + 2))
		{
			dprintf(1, "Sprite found\n");
			return (*ptr);
		}
		ptr = &((*ptr)->next);
	}
	dprintf(1, RED"Sprite NOT found\n"RST);

	return (NULL);
}

void	add_spr_to_list(t_spr_list *s_list, t_sprite *s)
{
	t_spr_list ret;

	dprintf(1, "Add spr to list\n");
	ret.s = s;
	ret.next = s_list;
	*s_list = ret;
}

void    add_sprite(t_map *m, int posX, int type)
{
	t_sprite *list;
	t_sprite *tmp;
	t_sprite *s;

	dprintf(1, GRN"Found sprite "DCYAN"-> posX: %d - posY: %d\n"RST, posX, m->height);
	s = init_sprite(m, new_point(posX, m->height), type);
	if (s != NULL)
	{
		s->next = m->sprites;
		m->sprites = s;
	}
	else
		ft_putstr(RED"Failed to malloc sprite\n"RST);
}

void	draw_sprite(void *brain, t_sprite *s)
{
	t_brain *b;
	double	s_size;
	double dist;
	int x;
	int y;
	int color;
	t_fpoint ratio;

	b = (t_brain *)brain;
	dist = calc_dist(*b->player->pos, s->pos);
	s_size = ((b->map->bloc_size) / dist) * b->player->cam->proj_dist;
	s_size =128;
	ratio.y = s->model->height / s_size;
	x = 0;
	
	/*
	while (x < s_size)
	{
		ratio.x =  (x % s->model->width + 1) * (s->model->width / b->map->bloc_size);
		y = 1;
		while (y < s_size)
		{
			color = pixel_get(s->model, x, y);
			if (color != 0x980088)
				pixel_put_buff(500 + x, 500 + y , color, b->map->frame);
			y++;
		}
		x++;
	}*/
}

void	disp_sprites(t_sprite *s)
{
	int			i;
	t_sprite **ptr;
	
	i = 0;
	ptr = &s;
	if (*ptr != NULL)
	{
		while (*ptr != NULL)
		{
			dprintf(1, "Sprite %d of type %d\n", i, (*ptr)->type);
			disp_point(&((*ptr)->pos));
			ptr = &((*ptr)->next);
			i++;
		}
		dprintf(1, "End of loop\n");
	} else {
		dprintf(1, "No sprites in list\n");
	}
}

void	disp_sprt_list(t_spr_list *s_list)
{
	int			i;
	t_spr_list **ptr;
	t_sprite	*s;	
	i = 0;
	ptr = &s_list;
	if (*ptr != NULL)
	{
		while (*ptr != NULL)
		{
			s = (*ptr)->s;
			dprintf(1, "Sprite %d of type %d\n", i, s->type);
			disp_point(&(s->pos));
			ptr = &((*ptr)->next);
			i++;
		}
		dprintf(1, "End of loop\n");
	} else {
		dprintf(1, "No sprites in list\n");
	}
}

void    reorder_sprites(t_map *m)
{
	
}