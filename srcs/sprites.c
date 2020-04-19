/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/19 01:33:07 by siferrar         ###   ########lyon.fr   */
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
	s->pos.x = pos.x * m->bloc_size + m->bloc_size/2;
	s->pos.y = pos.y * m->bloc_size + m->bloc_size/2;
	s->model = NULL;
	s->on_screen = 0;
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
	t_sprite **ptr;
	t_fpoint in_grid;
	t_sprite *sprites;

	//dprintf(1, "Getting sprite\n");

	sprites = (t_sprite *)m->sprites;
	ptr = &sprites;
	while (*ptr != NULL)
	{
		//dprintf(1, "Check Sprites x:%f y:%f  VS x:%f y:%f \n", (*ptr)->pos.x, (*ptr)->pos.y, p.x, p.y);
		if (compare((*ptr)->pos, p, m->bloc_size + 2))
		{
			//dprintf(1, "Sprite found\n");
			return (*ptr);
		}
		ptr = &((*ptr)->next);
	}
	//dprintf(1, RED"Sprite NOT found\n"RST);

	return (NULL);
}

void	add_spr_to_list(t_spr_list *s_list, t_sprite *s)
{
	t_sprite **ret;
	int i;

	i = 0;
	dprintf(1, YELO"Add spr to list\n");
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
	dprintf(1, GRN"Add spr to list OK\n"RST);
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
	if (s_list->list != NULL)
	{
		dprintf(1, "%d sprites in list\n", s_list->length);
		while (i < s_list->length)
		{
			disp_sprite(s_list->list[i]);
			i++;
		}
		dprintf(1, "End of loop\n");
	} else {
		dprintf(1, "No sprites in list\n");
	}
	ft_putstr(RST);
}

void	disp_sprite(t_sprite *s)
{
	dprintf(1, "Sprite of type %d\n", s->type);
	disp_point(&(s->pos));
}


void	draw_sprite(void *brain, t_sprite *s, float col)
{
	t_brain		*b;
	t_fpoint	s_size;
	t_fpoint	s_dist;
	t_fpoint	ratio;
	double		dist;
	double		angle;
	int		start_y;
	int		start_x;
	int			color;
	int			y;
	int x;
	int			texture_col;
	b = (t_brain *)brain;
	
	dist = calc_dist(*b->player->pos, s->pos);

	s_dist.x = s->pos.x - b->player->pos->x;
	s_dist.y = s->pos.y - b->player->pos->y;
	
	s_size.x = s->model->width * b->ctx->width / s->dist;
	s_size.y = s->model->height * b->ctx->height / s->dist;

	angle = atan2(s_dist.y, s_dist.x);
	angle = ft_indeg(to_360(b->player->angle - angle));
	
	//dprintf(1, "Angle: %f\n", angle);
	col = b->ctx->width / ft_indeg(b->player->cam->fov);
	//dprintf(1, "col_ratio: %f\n", col);
	//dprintf(1, "Draw sprite\n");
	//ft_putstr("s_size: ");
	//disp_point(&s_size);
	if (angle >= 0 && angle < 180)
		start_x = (int)floor(b->ctx->width / 2 - (col * angle));
	else if (angle < 360)
		start_x = (int)floor(b->ctx->width / 2 + (col * (360 - angle)));

	start_x -= s_size.x/2;
	//start_y = (int)floor(b->ctx->height / 2 + b->player->z - s_size.y/2);
	start_y = (b->ctx->height / 2) * (1 + (1/ s->dist)) + b->player->z - s_size.y/2;
	
	//dprintf(1, "start [%d][%d]\n", start_x, start_y);
	ratio.x = s->model->width / s_size.x;
	ratio.y = s->model->height / s_size.y;
	//dprintf(1, "ratio [%f][%f]\n", ratio.x, ratio.y);

	x = 0;
	while (x < s_size.x)
	{
		y = 0;
		while (y < s_size.y)
		{
			color = pixel_get(s->model, x * ratio.x, y * ratio.y);			
			if (color != SPR_TRANSP && b->map->sprites->column[start_x + x] >= floor(dist))
				if (start_x + x > 0 && start_x + x < b->ctx->width
					&& start_y + y > 0 && start_y + y < b->ctx->height)
					pixel_put(start_x + x, start_y + y, color, b->map->frame);
			y++;
		}
		x++;
	}
}

void    sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt)
{
	float dist1;
	float dist2;
	int i;
	int j;

	i = 0;
	dprintf(1, CYAN"Order Sprites\n"RST);
	while (i < lst_sprt->length)
	{
		j = i;
		while (j < lst_sprt->length)
		{
			dist1 = calc_dist(*pos, lst_sprt->list[i]->pos);
			dist2 = calc_dist(*pos, lst_sprt->list[j]->pos);
			lst_sprt->list[i]->dist = dist1;
			lst_sprt->list[j]->dist = dist2;
			//dprintf(1, "%f vs %f\n", dist1, dist2);
			if (dist1 < dist2)
			{
			//	dprintf(1, "Swap [%d] and [%d]\n", i, j);
				//disp_sprite(lst_sprt->list[i]);
				//disp_sprite(lst_sprt->list[j]);
				swap_sprite(lst_sprt, i, j);
			}
			j++;
		}
		i++;
	}
	dprintf(1, CYAN"Order Sprites OK\n"RST);
}

float	deg_sprite(t_player *ply, t_spr_list *spr)
{
	float angle;
	t_fpoint s_dist;
	int i;
	
	i = 0;
	while(i < spr->length)
	{
		s_dist.x = spr->list[i]->pos.x - ply->pos->x;
		s_dist.y = spr->list[i]->pos.y - ply->pos->y;
		angle = atan2(s_dist.y, s_dist.x);
		angle = to_360(ply->angle - angle);	
		dprintf(1, "%f\t%f\n", ply->pos->x, ply->pos->y);
		dprintf(1, "angle : %f\n", ft_indeg(angle));
		spr->list[i]->deg = ft_indeg(angle);
		if((spr->list[i]->deg > (360 - ft_indeg(ply->cam->fov / 2))) 
			|| (spr->list[i]->deg < ft_indeg(ply->cam->fov / 2))) // a opti
			spr->list[i]->on_screen = 1;
		else
			spr->list[i]->on_screen = 0;
		dprintf(1, "on_scr : %d\n", spr->list[i]->on_screen);
		i++;
	}
}

void	update_sprite(t_brain *b)
{
	int i;
	
	i = 0;
	sort_sprites(b->player->pos, b->map->sprites);
	//deg_sprite(b->player, b->map->sprites);
	while(i < b->map->sprites->length)
	{
		draw_sprite(b, b->map->sprites->list[i], 0);
		i++;
	}
}