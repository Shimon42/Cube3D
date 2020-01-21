/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 17:22:11 by siferrar    ###    #+. /#+    ###.fr     */
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
	printf("Map Print\nWidth: %d\nHeight:%d\n", map->width, map->height);
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->grid[x][y] == 0)
				ft_putstr(DGREY);
			else if (map->grid[x][y] == 1)
				ft_putstr(DCYAN);
			else if (map->grid[x][y] == 2)
				ft_putstr(YELO); 
			ft_putchar(map->grid[x][y] + '0');
			y++;
		}
		ft_putchar('\n');
		x++;
	}
	ft_putchar('\n');
}

int				init_map(t_map **map)
{
	(*map) = malloc(sizeof(t_map));
	(*map)->height = 0;
	(*map)->width = 0;
	alloc_map(map);

	return (1);
}

int			**init_2d_tab(int width, int height)
{
	int **new;
	int i;

	i = 0;
	new = malloc((width) * sizeof(int **));
	while (i < width)
		new[i++] = malloc(height * sizeof(int *));
	return (new);
}

int			parse_values(t_map *map, char *line)
{
	int x;
	int i;

	x = 0;
	i = 0;
	while (x < map->width)
	{
		map->grid[x][map->height - 1] = line[i] - '0';
		while (*line + i  == ' ')
			i++;
		x++;
	}
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
		add_map_row(b->map, line);
		parse_values(b->map, line);
		if (!ret)
			break;
	}
	printf(GRN"MAP READ - OK"RST"\n");
	printf("Width: [%d]\n", b->map->width);
	printf("Height:[%d]\n", b->map->height);
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


int			add_map_row(t_map *map, char *line)
{
	int **new;
	int x;
	int y;

	y = 0;
	x = 0;
	if (!map->width)
		map->width = line_length(line);
	new = alloc_2d_tab(map->width, map->height);
	if (map->grid)
	{
		while (x < map->width - 1)
		{
			y = 0;
			while (y < map->height - 1)
			{
				new[x][y] = map->grid[x][y];
				y++;
			}
			x++;
		}
	}
	map->height++;
	map->grid = new;
	return (1);
}


int			**alloc_2d_tab(int width, int height)
{
	int **new;
	int x;

	x = 0;
	new = malloc((width + 1) * sizeof(int **));
	new[width + 1] = 0;
	while (x < width + 1)
		new[x++] = malloc((height + 1) * sizeof(int *));
	//new[x - 1][(height++)] = 0;	
	return (new);
}

int			alloc_map(t_map **map)
{
	int **new;
	int x;

	x = 0;
	new = malloc(((*map)->width + 1) * sizeof(int **));
	new[(*map)->width + 1] = 0;
	while (x < (*map)->width + 1)
		new[x++] = malloc(((*map)->height + 1) * sizeof(int *));
	new[x - 1][((*map)->height)] = 0;	
	(*map)->grid = new;
	return (1);
}