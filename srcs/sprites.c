/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/16 13:10:02 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_sprite   *init_sprite(t_map *m, t_fpoint pos, int type)
{
	t_sprite	*s;
	t_brain		*b;

	dprintf(1, "Init Sprite\n");
	b = (t_brain *)m->brain;
	if (!(s = malloc(sizeof(t_sprite))))
		return (NULL);
	s->pos = pos;
	s->pos.x = pos.x * m->bloc_size;
	s->pos.y = pos.y * m->bloc_size;
	s->model = NULL;
	init_texture(b, "./assets/sprites/barrel.xpm", &s->model);
	s->type = 2;
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
	t_fpoint in_grid;
	int i;

	//dprintf(1, "Getting sprite\n");
	i = 0;
	while (i < m->sprites->length)
	{
		//dprintf(1, "Check Sprites x:%f y:%f  VS x:%f y:%f \n", (*ptr)->pos.x, (*ptr)->pos.y, p.x, p.y);
		if (compare(m->sprites->list[i]->pos, p, m->bloc_size + 2))
		{
			//dprintf(1, "Sprite found\n");
			return (m->sprites->list[i]);
		}
		i++;
	}
	//dprintf(1, RED"Sprite NOT found\n"RST);

	return (NULL);
}

void	add_spr_to_list(t_spr_list *s_list, t_sprite *s)
{
	t_sprite **ret;
	int i;
	int new_len;

	i = 0;
	//dprintf(1, YELO"Add spr to list\n");
	//disp_sprite(s);
	if (s_list == NULL)
	{
	//	dprintf(1, "-- Init List\n");
		s_list = malloc(sizeof(t_spr_list));
		s_list->length = 0;
		s_list->list = NULL;
	}
	ret = malloc((s_list->length + 1) * sizeof(t_sprite *));
	if (s_list->list != NULL && s_list->length != 0)
	{
		while (i < s_list->length)
		{
			ret[i] = s_list->list[i];
			i++;
		}
		free(s_list->list);
	}

	ret[i] = s;
	s_list->list = ret;
	s_list->length++;
	//dprintf(1, GRN"Add spr to list OK\n"RST);
}

void    swap_sprite(t_spr_list *lst_sprt, int num1, int num2)
{
	if((num1 < lst_sprt->length) && (num2 < lst_sprt->length) && (num1 != num2))
	{
		t_sprite temp;
		t_sprite *spr_a;
		t_sprite *spr_b;

		spr_a = lst_sprt->list[num1];
		spr_b = lst_sprt->list[num2];
		temp.dist = spr_a->dist;
		temp.pos = spr_a->pos;
		spr_a->dist = spr_b->dist;
		spr_a->pos = spr_b->pos;
		spr_b->dist = temp.dist;
		spr_b->pos = temp.pos;
	}
}


void	disp_sprites(t_spr_list *s_list)
{
	int			i;
	t_sprite	*s;
	i = 0;
	ft_putstr(PINK);
	if (s_list != NULL && s_list->list != NULL)
	{
		//dprintf(1, "%d sprites in list\n", s_list->length);
		while (i < s_list->length)
		{
			disp_sprite(s_list->list[i]);
			i++;
		}
	//	dprintf(1, "End of loop\n");
	} else {
		//dprintf(1, "No sprites in list\n");
	}
	ft_putstr(RST);
}

void    sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt)
{
	float dist1;
	float dist2;
	int i;
	int j;

	i = 0;
	//dprintf(1, CYAN"Order Sprites\n"RST);
	while (i < lst_sprt->length)
	{
		j = i;
		while (j < lst_sprt->length)
		{
			dist1 = calc_dist(*pos, lst_sprt->list[i]->pos);
			dist2 = calc_dist(*pos, lst_sprt->list[j]->pos);
			lst_sprt->list[i]->dist = dist1;
			lst_sprt->list[j]->dist = dist2;
		//	dprintf(1, "%f vs %f\n", dist1, dist2);
			if (dist1 > dist2)
			{
				//dprintf(1, "Swap [%d] and [%d]\n", i, j);
				disp_sprite(lst_sprt->list[i]);
				disp_sprite(lst_sprt->list[j]);
				swap_sprite(lst_sprt, i, j);
			}
			j++;
		}
		i++;
	}
	//dprintf(1, CYAN"Order Sprites OK\n"RST);
}

void	draw_sprite(void *brain, t_sprite *s, float col)
{
	t_brain		*b;
	t_fpoint	s_size;
	t_fpoint	s_dist;
	t_fpoint	ratio;
	double		dist;
	double		angle;
	float		start_y;
	int			color;
	int			y;
	int			texture_col;

	b = (t_brain *)brain;
	
	ft_putstr(RST);
	dist = calc_dist(*b->player->pos, s->pos);

	
	s_size.x = s->model->width * b->ctx->width / dist;
	s_size.y = s->model->height * b->ctx->height / dist;
	s_dist.x = abs(s->pos.x - b->player->pos->x);
	s_dist.y = abs(s->pos.y - b->player->pos->y);

	angle = atan2(s_dist.y, s_dist.x);
	angle = b->player->angle - angle;
	
	start_y = (b->ctx->height / 2) * (1 + (1 / dist)) - s_size.y/2;
	ratio.x = s_size.x / b->map->bloc_size;
	ratio.y = s_size.y / b->map->bloc_size;

	y = 0;
	dprintf(1, "size: %f %f\n", s_size.x, s_size.y);
	ft_putstr("s_dist:");
	disp_point(&s_dist);
	ft_putstr("Ratio:");
	disp_point(&ratio);
	while (y < s_size.y)
	{
		//color = pixel_get(s->model, (int)floor(s->hit.x) % b->map->bloc_size, y * ratio.y);
		color = 0xFF0000;
		pixel_put(col, start_y + y, color, b->map->frame);
		y++;
	}
}


void draw_sprites(void *brain, t_spr_list *lst, int col)
{
	int i;

	i = 0;
	//dprintf(1, GRN"DRAW SPRITES\n"RST);
	while (i < lst->length)
	{
		draw_sprite(brain, lst->list[i], col);
		i++;
	}
}

void	update_sprite(t_brain *b)
{
	sort_sprites(b->player->pos, b->map->sprites);
}

void	disp_sprite(t_sprite *s)
{
	dprintf(1, "Sprite of type %d\n", s->type);
	disp_point(&(s->pos));
	dprintf(1, "Hit at:");
	if (&s->hit != NULL)
		disp_point(&s->hit);
}