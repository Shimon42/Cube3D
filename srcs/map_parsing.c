/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 18:13:53 by siferrar    ###    #+. /#+    ###.fr     */
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
	(*map)->bloc_size = 10;

	return (1);
}

int				open_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;

	init_map(&b->map);

	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		add_map_row(b->map, line);
		if (!ret)
			break;
	}
	ft_putstr(b->map->grid);
	printf(GRN"\nMAP READ - OK"RST"\n");
	printf("Width: [%d]\n", b->map->width);
	printf("Height:[%d]\n", b->map->height);
	print_map_grid(b->map);
	close(file);
	draw_minimap(b, 10, 10, 1);
	draw_minimap(b, 10, 180, 2.5);
	draw_minimap(b, 10, 560, 3);
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

int			add_map_row(t_map *map, char *line)
{
	char	*new;
	char	*temp;
	int		i;

	i = 0;
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
		}
		i++;
	}
	map->height++;
	map->grid = new;
	return (1);
}
