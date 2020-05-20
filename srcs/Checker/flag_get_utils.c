/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:20:59 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/20 14:11:35 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	ft_check_struct(t_type *map)
{
	if ((map->res[2] == 0) || ((map->f[3] == 0) || (map->c[3] == 0)))
		exit_flag(512, "The setup file lacks one or more information\n", map);
	if (map->no[0] == 0)
		exit_flag(513, "North texture missing\n", map);
	if (map->so[0] == 0)
		exit_flag(514, "South texture missing\n", map);
	if (map->ea[0] == 0)
		exit_flag(515, "East texture missing\n", map);
	if (map->we[0] == 0)
		exit_flag(516, "West texture missing\n", map);
	if (map->s[0] == 0)
		exit_flag(517, "Sprite texture missing\n", map);
}

int		ft_strmultichr(char *str, char *chrlst)
{
	int		i;
	int		flaged;
	char	*ptr;

	i = 0;
	ptr = NULL;
	flaged = 1;
	if ((ft_strlen(str) == 0) || ((str == NULL) && (chrlst == NULL)))
		return (0);
	while (str[i])
	{
		if (!(ptr = ft_strchr(chrlst, str[i])))
			flaged = 0;
		i++;
	}
	return (flaged);
}

int		ft_ext_check(char *str, char *end)
{
	int	len;
	int	count;

	len = ft_strlen(str) - 1;
	count = ft_strlen(end) - 1;
	if (len == count)
		return (0);
	while ((str[len--] == end[count]) && ((count > 0) && (len > 0)))
		count--;
	if (count == 0)
		return (1);
	else
		return (0);
}

void	ft_init_t_type(t_type *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->s = NULL;
	map->c = NULL;
	map->f = NULL;
	map->height = 0;
	map->width = 0;
	map->valid = 1;
	map->res[0] = 0;
	map->res[1] = 0;
	map->res[2] = 0;
}

void	exit_flag(int err_num, char *str, t_type *map)
{
	ft_putstr(RED "Cub3d Exit - Error: ");
	ft_putnbr(err_num);
	ft_putstr(" - ");
	ft_putstr(str);
	ft_putstr("\n");
	free(map);
	exit(0);
}
