/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:36:43 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/15 18:10:19 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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

void init_texture(t_brain *b, char *path, t_buff **t)
{
	dprintf(1, DCYAN"	-> %s", path);
	*t = malloc(sizeof(t_buff));
	if (*t)
	{
		(*t)->initied = 1;
		(*t)->img = mlx_xpm_file_to_image(b->ctx->mlx_ptr, path, &(*t)->width, &(*t)->height);
		if (!(*t)->img)
			exit_cube(NULL, 404, path, 0);
		(*t)->initied = 2;
		(*t)->addr = mlx_get_data_addr((*t)->img, &(*t)->bits_per_pixel, &(*t)->line_length,
									&(*t)->endian);
		(*t)->max_addr = (*t)->line_length * (*t)->height;
		(*t)->offset = (*t)->bits_per_pixel / 8;
		(*t)->initied = 3;
		dprintf(1, GRN" - OK\n"RST);
	}
	else
		exit_cube(NULL, 401, "Failed to malloc texture", 0);
}

int				open_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;
	t_player_detect *player;

	init_map(b->ctx, b);

	ft_putstr(CYAN"Init Textures\n");
	init_texture(b, "./assets/textures/walls/stone_bricks/2.xpm", &b->map->w_n);
	init_texture(b, "./assets/textures/walls/stone_bricks/4.xpm", &b->map->w_e);
	init_texture(b, "./assets/textures/walls/stone_bricks/3.xpm", &b->map->w_s);
	init_texture(b, "./assets/textures/walls/stone_bricks/1.xpm", &b->map->w_w);
	//init_texture(b, "./assets/textures/colors/blue.xpm", &b->map->floor);
	init_texture(b, "./assets/textures/floor/sand.xpm", &b->map->floor);
	//init_texture(b, "./assets/sky/zenith.xpm", &b->map->skybox);
	init_texture(b, "./assets/sky/mountains/mountains.xpm", &b->map->skybox);
	
	player = malloc(sizeof(t_player_detect));
	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		player = add_map_row(b->map, line);
		if (player != NULL)
		{
			printf(CYAN"Player found: "DCYAN"%d"RST"\n", player->pos_x);
			init_player(b, player->pos_x, player->direction);
		}
		if (!ret)
			break;
	}
	close(file);
	dprintf(1, CYAN"Map Readed - "GRN"OK - "DYELO"Code: %d\n"RST, ret);
	dprintf(1, DCYAN"	-> Width: [%d]\n", b->map->width);
	dprintf(1, "	-> Height:[%d]\n\n"RST, b->map->height);
	print_map_grid(b->map);
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	dprintf(1,DCYAN"\nReal Size : %d x %d px\n", b->map->px_width, b->map->px_height);
	ft_putstr(GRN"Map Parsing OK\n"RST);
	free(player);
	return (1);
}

size_t		line_length(char *line)
{
	size_t len;

	len = 0;
	while (*line)
		if (*line++ != ' ')
			len++;
	return (len);
}

t_player_detect		*add_map_row(t_map *m, char *line)
{
	char	*new;
	char	*temp;
	int		i;
	int		real;
	t_player_detect	*player;

	i = 0;
	real = 0;
	player = NULL;
	new = NULL;
	if (!m->grid)
		m->grid = ft_calloc(line_length(line) + 1, sizeof(char));
	else
		new = m->grid;
	m->width = line_length(line);
	while (line[i])
	{
		if (line[i] != ' ')
		{
			temp = ft_strnjoin(new, line + i, 0, 1);
			free(new);
			new = temp;
			if (line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W')
			{
				player = malloc(sizeof(t_player_detect));
				player->pos_x = real;
				player->direction = line[i];
			}
			if (line[i] == '2')
				add_sprite(m, real, 2);
			real++;
		}
		i++;
	}
	m->height++;
	m->grid = new;
	return (player);
}
