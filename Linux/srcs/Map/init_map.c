/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:36:43 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/28 09:44:54 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void				init_map(t_ctx *ctx, void *brain)
{
	t_brain *b;

	b = (t_brain *)brain;
	if (!(b->map = malloc(sizeof(t_map))))
		exit_cube(brain, 122, "WTFFFFFF", 0);
	b->map->height = 0;
	b->map->width = 0;
	b->map->grid = NULL;
	b->map->scale = 1;
	b->map->bloc_size = 64;
	b->map->w_n = NULL;
	b->map->w_e = NULL;
	b->map->w_s = NULL;
	b->map->w_w = NULL;
	b->map->floor = NULL;
	if (!(b->map->sprites = malloc(sizeof(t_spr_list))))
		exit_cube(brain, 120, "malloc failing for number of sprites in map", 0);
	if (!(b->map->sprites->column = malloc(b->ctx->width * sizeof(float))))
		exit_cube(brain, 121, "malloc failing for the distance array", 0);
	b->map->sprites->length = 0;
	b->map->sprites->list = NULL;
	b->map->skybox = NULL;
	b->map->brain = b;
	init_buff(ctx, &b->map->frame, ctx->width, ctx->height);
	b->map->is_valid = 1;
}

void				init_textures(t_brain *b, t_type *map)
{
	b->map->default_spr = NULL;
	ft_putstr(CYAN"Init Textures\n");
	init_texture(b, map->no, &b->map->w_n);
	init_texture(b, map->ea, &b->map->w_e);
	init_texture(b, map->so, &b->map->w_s);
	init_texture(b, map->we, &b->map->w_w);
	init_texture(b, map->f, &b->map->floor);
	init_texture(b, map->c, &b->map->skybox);
	init_texture(b, map->s, &b->map->default_spr);
}

int					realloc_map(t_map *m, char *line)
{
	t_map_line	**grid;
	int			y;
	int			len;

	len = ft_strlen(line);
	if (len > m->width)
		m->width = len;
	y = 0;
	grid = ft_calloc(m->height + 1, sizeof(t_map_line *));
	while (y < m->height)
	{
		grid[y] = m->grid[y];
		y++;
	}
	grid[y] = malloc(sizeof(t_map_line));
	grid[y]->length = len;
	grid[y]->line = ft_str_to_int_tab(line);
	free(line);
	free(m->grid);
	m->grid = grid;
	m->height++;
	return (1);
}

t_player_detect		*chr_trt(char *line, t_map *m)
{
	t_player_detect	*player;
	int				i;
	int				real;

	i = -1;
	player = NULL;
	while (line[++i])
	{
		line[i] = (line[i] == ' ' ? '0' - 1 : line[i]);
		if (line[i] != '\0' && ft_strchr("NESW", line[i]) != NULL)
		{
			if (player == NULL)
			{
				player = malloc(sizeof(t_player_detect));
				player->pos_x = i;
				player->direction = line[i];
			}
		}
		if ((real = line[i] - '0') >= 2 && real <= 4)
			add_spr_to_list(m->sprites,
							init_sprite(m, new_fpoint(i, m->height), real));
	}
	return (player);
}

t_player_detect		*add_map_row(t_map *m, char *line)
{
	t_player_detect	*player;
	t_brain			*b;

	b = (t_brain *)m->brain;
	if (((ft_strmultichr(line, " 01234SNEW")) == 0)
			&& (ft_strlen(line) != 0))
		m->is_valid = 0;
	player = chr_trt(line, m);
	realloc_map(m, line);
	return (player);
}
