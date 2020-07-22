/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:39:19 by milosand          #+#    #+#             */
/*   Updated: 2020/07/22 15:39:40 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		pre_check(char *path, t_type *map)
{
	int	fd;

	fd = -1;
	map = malloc(sizeof(t_type));
	if (map == NULL)
		return (-1);
	if (ft_ext_check(path, ".cub"))
		fd = open(path, O_RDONLY);
	else
		exit_flag(500, "please provide .cub file\n", map);
	return (fd);
}

t_type	*ft_getmap_flag(char *path)
{
	int		ret;
	int		fd;
	char	*line;
	t_type	*map;

	fd = pre_check(path, map);
	if (fd > 0)
	{
		map->res[0] = 0;
		ft_init_t_type(map);
		ret = get_next_line(fd, &line);
		while (ret && ((ft_strmultichr(line, " 01234SNEW")) != 1))
		{
			ft_getmap_values(line, map);
			free(line);
			ret = get_next_line(fd, &line);
		}
		ft_check_struct(map);
		free(line);
		close(fd);
		return (map);
	}
	else
		return (NULL);
}

void	ft_getmap_values(char *line, t_type *map)
{
	int	res;

	if (!(res = ft_strncmp(line, "R ", 2)))
		ft_flag_res(line + 2, map->res, map);
	else if (!(ft_strncmp(line, "NO ", 3)))
		ft_flag_str(line + 3, &map->no, map);
	else if (!(ft_strncmp(line, "SO ", 3)))
		ft_flag_str(line + 3, &map->so, map);
	else if (!(ft_strncmp(line, "WE ", 3)))
		ft_flag_str(line + 3, &map->we, map);
	else if (!(ft_strncmp(line, "EA ", 3)))
		ft_flag_str(line + 3, &map->ea, map);
	else if (!(ft_strncmp(line, "S ", 2)))
		ft_flag_str(line + 2, &map->s, map);
	else if (!(ft_strncmp(line, "F ", 2)))
		ft_flag_str(line + 2, &map->f, map);
	else if (!(ft_strncmp(line, "C ", 2)))
		ft_flag_str(line + 2, &map->c, map);
	else if (line[0] != '\0')
		exit_flag(501, "Unkown identifier(s) in setup file\n", map);
}
