/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 17:57:32 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_putstr(char *str)
{
	size_t len;

	if (str)
	{
		len = ft_strlen(str);
		write(1, str, len);
	}
}

void print_map_debug(char *line)
{
	while (*line)
	{
		if (*line == '0')
			ft_putstr(DGREY);
		else if (*line == '1')
			ft_putstr(DCYAN);
		else if (*line == '2')
			ft_putstr(YELO); 
		ft_putchar(*line++);
	}
	ft_putchar('\n');
}

void print_map_grid_debug(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("Width: %d\n", map->width);
	printf("Height: %d\n", map->height);
	/*while (x < map->width)
	{
		while (y < map->height)
		{
			if (map->grid[x][y] == '0')
				ft_putstr(DGREY);
			else if (map->grid[x][y] == '1')
				ft_putstr(DCYAN);
			else if (map->grid[x][y] == '2')
				ft_putstr(YELO); 
			
			ft_putchar(map->grid[x][y]);
			y++;
		}
		x++;
	}*/
	ft_putchar('\n');
}

int				init_map(t_map **map)
{
	(*map) = malloc(sizeof(t_map));
	(*map)->height = 0;
	(*map)->width = 0;
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
		print_map_debug(line);
		parse_map(&b->map, line);
		if (!ret)
			break;
	}
	printf(GRN"MAP READ - OK"RST"\n");
	print_map_grid_debug(b->map);
	close(file);
	return (1);
}

size_t		line_length(char *line)
{
	size_t len;

	len = 0;
	while (*line)
	{
		if (*line++ != ' ')
			len++;
	}
	return (len);
}

int			parse_map(t_map **map, char *line)
{
	int i;

	i = 0;
	if (!(*map)->width)
		(*map)->width = line_length(line);
	alloc_map(map);
	/*while (line[i])
	{
		(*map)->grid[i][(*map)->height] = line[i] - '0';
	}*/
	return (1);
}

int			alloc_map(t_map **map)
{
	int **new;
	int i;

	i = 0;
	new = malloc(((*map)->width + 1) * sizeof(short **));
	new[(*map)->width + 1] = 0;
	while (i < (*map)->width + 1)
		new[i++] = malloc(((*map)->height + 1) * sizeof(short *));
	new[i - 1][((*map)->height++)] = 0;

	
	(*map)->grid = new;
	return (1);
}