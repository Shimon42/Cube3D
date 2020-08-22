/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:29:02 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/22 11:23:52 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		ft_charcount(char *str, char cara)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == cara)
			count++;
		i++;
	}
	return (count);
}

int		ft_flag_color(t_type *map, char *str)
{
	int		i;
	char	**splited;
	t_rgb	target;

	if (ft_check_str(str, "0123456789, ") || (ft_charcount(str, ',') != 2))
		exit_flag(520, "Illegal character in color declaration\n", map);
	i = 0;
	splited = ft_split(str, ',');
	while (splited[i] != NULL)
		i++;
	if (i != 3)
		exit_flag(520, "not a color\n", map);
	i = 0;
	target.r = ft_atoi_ovr(splited[0]);
	target.g = ft_atoi_ovr(splited[1]);
	target.b = ft_atoi_ovr(splited[2]);
	ft_free_split(splited);
	if ((target.r > 255) || (target.r < 0)
		|| (target.g > 255) || (target.g < 0)
		|| (target.b > 255) || (target.b < 0))
		exit_flag(520, "One of the colors is not formatted correctly\n", map);
	return (rgb_to_hex(target));
}

void	ft_flag_str(char *str, char **target, t_type *map)
{
	int	fd;

	while (*str == ' ')
		str++;
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
	else if (*target == NULL)
		*target = ft_itoa(ft_flag_color(map, str));
	else
		exit_flag(503, "Several textures provided for one identifiers", map);
}

void	size_capper(int *size, int cap)
{
	if (*size < cap)
	{
		ft_printf("setting size to the minimum allowed of %d\n", cap);
		*size = cap;
	}
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
	ft_free_split(splited);
	if (i != 2)
		exit_flag(511, "Resolution not good\n", map);
	target[0] = ft_atoi_ovr(str);
	str = ft_strchr(str, ' ');
	target[1] = ft_atoi_ovr(str);
	size_capper(&target[0], 100);
	size_capper(&target[1], 100);
	target[2] = 1;
}
