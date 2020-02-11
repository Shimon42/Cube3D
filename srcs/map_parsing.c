/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 20:52:39 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int				init_map(t_map **map)
{
	(*map) = malloc(sizeof(t_map));
	(*map)->height = 0;
	(*map)->width = 0;
	(*map)->grid = NULL;
	(*map)->scale = 1;
	(*map)->bloc_size = 64;
	(*map)->w_n = 0xFF0000;
	(*map)->w_e = 0xFFFF00;
	(*map)->w_s = 0x0000FF;
	(*map)->w_w = 0x00FF00;
	return (1);
}

int				open_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;
	t_player_detect *player;

	init_map(&b->map);
	player = malloc(sizeof(t_player_detect));
	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		player = add_map_row(b->map, line);
		if (player != NULL)
		{
			printf(CYAN"Player found: %d"RST"\n", player->pos_x);
			init_player(b, player->pos_x, player->direction);
		}
		if (!ret)
		{
			printf(YELO"End of get map - Code: %d\n"RST, ret);
			break;
		}/* else
			printf("Readed: [%s]\n", line);*/
	}
	close(file);
	//ft_putstr(b->map->grid);
	printf(GRN"MAP READ - OK"RST"\n");
	printf(DCYAN" -> Width: [%d]\n", b->map->width);
	printf(" -> Height:[%d]\n"RST, b->map->height);
	print_map_grid(b->map);
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	printf("Real Width: %d\n", b->map->px_width);
	printf("Real Height: %d\n", b->map->px_height);
	ft_putstr("Map Parsing OK\n");
	free(player);
	//draw_minimap(b, 10, 10, 1);
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

t_player_detect		*add_map_row(t_map *map, char *line)
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
	if (!map->grid)
		map->grid = ft_calloc(line_length(line) + 1, sizeof(char));
	else
		new = map->grid;
	map->width = line_length(line);
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
			real++;
		}
		i++;
	}
	map->height++;
	map->grid = new;
	return (player);
}
