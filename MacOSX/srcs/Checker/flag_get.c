/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:39:19 by milosand          #+#    #+#             */
/*   Updated: 2020/07/22 15:05:22 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_type	*ft_getmap_flag(char *path)
{
	int		ret;
	int		fd;
	char	*line;
	t_type	*map;

	map = malloc(sizeof(t_type));
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		map->res[0] = 0;
		ft_init_t_type(map);
		ret = get_next_line(fd, &line);
		while (ret && ((ft_strmultichr(line, " 012SNEW")) != 1))
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

void	ft_flag_str(char *str, char **target, t_type *map)
{
	int	fd;

	if (ft_ext_check(str, ".xpm"))
	{
		if (*target != NULL)
			exit_flag(502,
				"Several textures provided for one identifiers\n", map);
		if ((fd = open(str, O_RDONLY)) == -1)
			exit_flag(503, "Invalid path for one of the textures\n", map);
		*target = ft_strdup(str);
		close(fd);
	}
	else
		exit_flag(504, "Please provide a \'.xpm\' file.\n", map);
}

void	ft_flag_res(char *str, int *target, t_type *map)
{
	int		i;
	char	**splited;

	i = 0;
	if (ft_check_str(str, "0123456789 "))
		exit_flag(509, "Illegal character in resolution\n", map);
	if (target[2] != 0)
		exit_flag(510, "Make up your mind about the resolution\n", map);
	splited = ft_split(str, ' ');
	while (splited[i] != NULL)
		i++;
	if (i != 2)
		exit_flag(511, "Resolution not gud\n", map);
	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
	target[0] = ft_atoi(str);
	str = ft_strchr(str, ' ');
	target[1] = ft_atoi(str);
	if (target[0] < 100)
		target[0] = 100;
	if (target[1] < 100)
		target[1] = 100;
	target[2] = 1;
}

char	*ft_check_str(char *str, char *chrs)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		while (chrs[i])
		{
			if (*str == chrs[i])
				flag = 1;
			i++;
		}
		if (flag == 0)
			return (str);
		flag = 0;
		i = 0;
		str++;
	}
	return (NULL);
}
