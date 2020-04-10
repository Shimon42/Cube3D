/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:36:43 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/10 15:08:49 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int				init_map(t_ctx *ctx, void *brain)
{
	t_brain *b;

	b = (t_brain *)brain;
	b->map = malloc(sizeof(t_map));
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
	b->map->sprites_count = 0;
	b->map->sprites = NULL;
	b->map->skybox = NULL;
	b->map->brain = b;
	init_buff(ctx, &b->map->frame, ctx->width, ctx->height);
	return (1);
}

void	init_textures(t_brain *b)
{
	ft_putstr(CYAN"Init Textures\n");
	init_texture(b, "./assets/textures/walls/stone_bricks/2.xpm", &b->map->w_n);
	init_texture(b, "./assets/textures/walls/stone_bricks/4.xpm", &b->map->w_e);
	init_texture(b, "./assets/textures/walls/stone_bricks/3.xpm", &b->map->w_s);
	init_texture(b, "./assets/textures/walls/stone_bricks/1.xpm", &b->map->w_w);
	init_texture(b, "./assets/textures/floor/sand.xpm", &b->map->floor);
	init_texture(b, "./assets/sky/mountains/mountains.xpm", &b->map->skybox);
	
}

int		realloc_map(t_map *m, char *line)
{
	t_map_line **grid;
	int y;
	int len;

	len = ft_strlen(line);
	if (len > m->width)
		m->width = len;
	y = 0;
	grid = ft_calloc(m->height + 2, sizeof(t_map_line *));
	while (y < m->height)
	{
		grid[y] = m->grid[y];
		y++;
	}
	grid[y] = malloc(sizeof(t_map_line));
	grid[y]->length = len;
	grid[y]->line = ft_str_to_int_tab(line);
	grid[++y] = NULL;
	m->grid = grid;
	m->height++;
	return (1);
}
t_player_detect		*add_map_row(t_map *m, char *line)
{
	int		*new;
	int		*temp;
	int		i;
	int		real;
	t_player_detect	*player;

	i = 0;
	real = 0;
	player = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			line[i] = '0' - 1;
		if (line[i] == 'N' || line[i] == 'E'
											|| line[i] == 'S' || line[i] == 'W')
		{
			player = malloc(sizeof(t_player_detect));
			player->pos_x = i;
			player->direction = line[i];
		}
		i++;
	}
	realloc_map(m, line);
	return (player);
}

int				open_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;
	t_player_detect *player;

	init_map(b->ctx, b);
	init_textures(b);
	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		if ((player = add_map_row(b->map, line)) != NULL)
			init_player(b, player->pos_x, player->direction);
		if (!ret)
			break;
	}
	close(file);
	dprintf(1, DCYAN"	-> Width: [%d]\n", b->map->width);
	dprintf(1, "	-> Height:[%d]\n\n"RST, b->map->height);
	print_map_grid((b->map));
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	dprintf(1,DCYAN"\nReal Size : %d x %d px\n", b->map->px_width,
												b->map->px_height);
	free(player);
	return (1);
}