/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 14:47:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 14:55:44 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	print_map_debug(t_map_line *line)
{
	int i;

	i = 0;
	while (i < line->length)
	{
		if (line->line[i] == 0)
			ft_putstr(DGREY);
		else if (line->line[i] == 1)
			ft_putstr(DCYAN);
		else if (line->line[i] >= 2 && line->line[i] < 5)
			ft_putstr(YELO);
		else if (line->line[i] > 5)
			ft_putstr(PINK);
		if (line->line[i] == -1)
			ft_putchar(' ');
		else
			ft_putnbr(line->line[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putstr(" - ");
	ft_putnbr(line->length);
	ft_putchar('\n');
}

void	print_map_grid(t_map *map)
{
	int y;

	y = 0;
	while (y < map->height)
	{
		print_map_debug(map->grid[y]);
		y++;
	}
}

void	disp_map_s(t_map *m)
{
	ft_printf(
	"\nMap:\n\tHeight: [%d]\n\tWidth: [%d]\n\tBloc Size: [%d]\n\tScale: [%f]\n",
	m->width, m->height, m->bloc_size, m->scale);
}
