/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:39:19 by milosand          #+#    #+#             */
/*   Updated: 2020/08/28 09:15:18 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		pre_check(char *path, t_type **map)
{
	int	fd;

	fd = -1;
	*map = malloc(sizeof(t_type));
	if (*map == NULL)
		return (-1);
	ft_init_t_type(*map);
	if (ft_ext_check(path, ".cub"))
		fd = open(path, O_RDONLY);
	else
		exit_flag(500, "please provide .cub file\n", *map);
	(*map)->fd = fd;
	return (fd);
}

t_type	*ft_getmap_flag(char *path)
{
	int		ret;
	int		fd;
	t_type	*map;

	map = NULL;
	fd = pre_check(path, &map);
	if (fd > 0)
	{
		map->res[0] = 0;
		ret = get_next_line(fd, &(map->line), 0);
		while (ret && ((ft_strmultichr(map->line, " 01234SNEW")) != 1))
		{
			ft_getmap_values(map->line, map);
			free(map->line);
			ret = get_next_line(fd, &(map->line), 0);
		}
		check_n_free(map->line);
		ft_check_struct(map);
	}
	else
		exit_flag(404, "Map file not found\n", map);
	ret = get_next_line(fd, &(map->line), 1);
	check_n_free(map->line);
	close(fd);
	return (map);
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
	{
		check_n_free(line);
		map->line = NULL;
		exit_flag(501, "Unkown identifier(s) in setup file\n", map);
	}
}

int		ft_atoi_ovr(const char *str)
{
	int			i;
	long long	res;
	int			sign;
	int			digits;

	sign = 1;
	res = 0;
	i = 0;
	digits = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		digits++;
	}
	if (digits > 6)
		return (9999999);
	return (res * sign);
}
