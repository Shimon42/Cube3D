/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 08:02:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/19 10:48:31 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
	return (s);
}

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

	if ((num1 < lst_sprt->length) && (num2 < lst_sprt->length) && (num1 != num2))
	{
		spr_a = lst_sprt->list[num1];
		spr_b = lst_sprt->list[num2];
		copy_sprite(spr_a, &temp);
		copy_sprite(spr_b, spr_a);
		copy_sprite(&temp, spr_b);
	}
}

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
	disp_point(&(s->pos));
}

t_rgb		hex_to_rgb(int color)
{
	t_rgb ret;

	ret.r = ((color >> 16) & 0xFF);
	ret.g = ((color >> 8) & 0xFF);
	ret.b = (color & 0xFF);
	return (ret);
}

int			rgb_to_hex(t_rgb color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

int			opacity(int color1, int color2, double opa)
{
	t_rgb	col1;
	t_rgb	col2;
	t_rgb	ret;

	col1 = hex_to_rgb(color1);
	col2 = hex_to_rgb(color2);
	ret.r = (int)floor(col1.r * opa) + (int)floor(col2.r * opa);
	ret.g = (int)floor(col1.g * opa) + (int)floor(col2.g * opa);
	ret.b = (int)floor(col1.b * opa) + (int)floor(col2.b * opa);
	return (rgb_to_hex(ret));
}

void		draw_sprite(void *brain, t_sprite *s, float col) // btranle col
{
	t_brain		*b;
	t_fpoint	s_size;
	t_fpoint	s_dist;
	t_fpoint	ratio;
	double		angle;
	int			start_y;
	int			start_x;
	int			color;
	int			y;
	int			x;
	int			texture_col;

	b = (t_brain *)brain;
	s_dist.x = s->pos.x - b->player->pos->x;
	s_dist.y = s->pos.y - b->player->pos->y;
	s_size.x = (b->map->bloc_size / s->dist) * b->player->cam->proj_dist;
	s_size.y = (b->map->bloc_size / s->dist) * b->player->cam->proj_dist;
	angle = atan2(s_dist.y, s_dist.x);
	angle = ft_indeg(to_360(b->player->angle - angle));
	col = b->ctx->width / ft_indeg(b->player->cam->fov);
	if (angle >= 0 && angle < 180)
		start_x = (int)floor(b->ctx->width / 2 - (col * angle));
	else if (angle < 360)
		start_x = (int)floor(b->ctx->width / 2 + (col * (360 - angle)));
	start_x -= s_size.x / 2;
	if (start_x + s_size.x < 0)
		return ;
	start_y = (b->ctx->height / 2) * (1 + (1 / s->dist)) + b->player->z - s_size.y / 2;
	//dprintf(1, "start [%d][%d]\n", start_x, start_y);
	ratio.x = s->model->width / s_size.x;
	ratio.y = s->model->height / s_size.y;
	//dprintf(1, "ratio [%f][%f]\n", ratio.x, ratio.y);
	x = 0;
	while (x < s_size.x)
	{
		if (b->map->sprites->column[start_x + x] >= floor(s->dist))
		{
			if (start_x + x > 0 && start_x + x < b->ctx->width)
			{
				y = 0;
				while (y < s_size.y)
				{
					if (start_y + y > 0 && start_y + y < b->ctx->height)
					{
						color = pixel_get(s->model, x * ratio.x, y * ratio.y);
						if (s->shadow != NULL)
						{
							col = pixel_get(s->shadow, x * ratio.x, y * ratio.y);
							if (col != SPR_TRANSP)
							{
								col = opacity(pixel_get(b->map->frame, start_x + x, start_y + y), col, 0.4);
								pixel_put(start_x + x, start_y + y, col, b->map->frame);
							}
						}
						if (color != SPR_TRANSP)
							pixel_put(start_x + x, start_y + y, color, b->map->frame);
					}
					y++;
				}
			}
		}
		x++;
	}
}

void		sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt)
{
	float	dist1;
	float	dist2;
	int		i;
	int		j;

	i = 0;
	//ft_printf(CYAN"Order Sprites\n"RST);
	while (i < lst_sprt->length)
	{
		j = i;
		while (j < lst_sprt->length)
		{
			dist1 = calc_dist(*pos, lst_sprt->list[i]->pos);
			//dist1 = cos((cur_col < divs.x ? -1 : 1) * (b->player->angle - cur_angle));
			dist2 = calc_dist(*pos, lst_sprt->list[j]->pos);
//			wall.dist *= cos((cur_col < divs.x ? -1 : 1)
//							* (b->player->angle - cur_angle));
			lst_sprt->list[i]->dist = dist1;
			lst_sprt->list[j]->dist = dist2;
			//dprintf(1, "%f vs %f\n", dist1, dist2);
			if (dist1 < dist2)
				swap_sprite(lst_sprt, i, j);
			j++;
		}
		i++;
	}
	//ft_printf(CYAN"Order Sprites OK\n"RST);
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
