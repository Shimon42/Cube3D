/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:16:27 by milosandric       #+#    #+#             */
/*   Updated: 2020/08/03 10:45:47 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void				get_map(t_brain *b, char *map_path)
{
	t_player_detect	*player;
	int				ret;
	int				file;
	char			*line;

	file = open(map_path, O_RDONLY);
	ret = get_next_line(file, &line);
	while (ret && ((ft_strmultichr(line, " 01SNEW")) != 1))
	{
		free(line);
		ret = get_next_line(file, &line);
	}
	while (ret != -1)
	{
		if ((player = add_map_row(b->map, line)) != NULL)
		{
			init_player(b, player->pos_x, player->direction);
			free(player);
		}
		if (!ret)
			break ;
		ret = get_next_line(file, &line);
	}
	free(player);
	close(file);
}

void				free_map_check(t_type *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map->s);
	free(map->f);
	free(map->c);
	free(map);
}

int					open_map(t_brain *b, char *map_path, t_type *map)
{
	init_map(b->ctx, b);
	b->map->frame->is_color = -1;
	init_textures(b, map);
	get_map(b, map_path);
	disp_sprites(b->map->sprites);
	if (b->player == NULL)
		exit_cube(NULL, 800, "No Player found in map", 0);
	sort_sprites(b->player->pos, b->map->sprites);
	ft_printf(DCYAN"	-> Width: [%d]\n", b->map->width);
	ft_printf("	-> Height:[%d]\n\n"RST, b->map->height);
	print_map_grid((b->map));
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	dprintf(1, DCYAN"\nReal Size : %d x %d px\n", b->map->px_width,
												b->map->px_height);
	free_map_check(map);
	return (1);
}
