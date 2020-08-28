/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:16:27 by milosandric       #+#    #+#             */
/*   Updated: 2020/08/28 09:55:30 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void				get_map(t_brain *b, char *map_path)
{
	t_player_detect	*player;
	int				ret;
	char			*line;

	b->cur_fd = open(map_path, O_RDONLY);
	ret = get_next_line(b->cur_fd, &line, 0);
	while (ret && ((ft_strmultichr(line, " 02341SNEW")) != 1))
	{
		free(line);
		ret = get_next_line(b->cur_fd, &line, 0);
	}
	while (ret != -1)
	{
		if ((player = add_map_row(b->map, line)) != NULL)
		{
			init_player(b, player, player->pos_x, player->direction);
			free(player);
		}
		if (!ret)
			break ;
		ret = get_next_line(b->cur_fd, &line, 0);
	}
	get_next_line(b->cur_fd, &line, 1);
	free(line);
}

void				free_map_check(t_type *map)
{
	get_next_line(map->fd, &(map->line), 1);
	check_n_free(map->line);
	check_n_free(map->no);
	check_n_free(map->so);
	check_n_free(map->we);
	check_n_free(map->ea);
	check_n_free(map->s);
	check_n_free(map->f);
	check_n_free(map->c);
	check_n_free(map);
}

int					open_map(t_brain *b, char *map_path, t_type *map)
{
	init_map(b->ctx, b);
	b->map->mini_map_width = b->ctx->width * 0.4;
	if (b->map->mini_map_width > 300)
		b->map->mini_map_width = 300;
	b->map->frame->is_color = -1;
	init_textures(b, map);
	free_map_check(map);
	get_map(b, map_path);
	if (b->player == NULL)
		exit_cube(NULL, 800, "No Player found in map", 0);
	sort_sprites(b->player->pos, b->map->sprites);
	ft_printf(DCYAN"	-> Width: [%d]\n", b->map->width);
	ft_printf("	-> Height:[%d]\n\n"RST, b->map->height);
	print_map_grid((b->map));
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	ft_printf(DCYAN"\nReal Size : %d x %d px\n", b->map->px_width,
												b->map->px_height);
	return (1);
}
