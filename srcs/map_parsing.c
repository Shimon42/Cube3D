/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 22:42:28 by siferrar    ###    #+. /#+    ###.fr     */
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

int				init_map(t_map *map)
{
	map = malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	return (1);
}

int				open_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;

	init_map(b->map);
	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		//parse_map(b->map, line);
		print_map_debug(line);
		if (!ret)
			break;
	}
	printf(GRN"MAP READ - OK"RST"\n");
	close(file);
	return (1);
}

int			parse_map(t_map *map, char *line)
{
	if (!map->width)
		map->width = ft_strlen(line);
	alloc_map(map);
	return (1);
}

int			alloc_map(t_map *map)
{
	int **new;
	int i;

	i = 0;
	new = malloc((map->width + 1) * sizeof(short **));
	new[map->width + 1] = 0;
	while (i < map->width + 1)
		new[i] = malloc((map->height + 1) * sizeof(short *));
	new[i][++map->height] = -1;
	return (1);
}