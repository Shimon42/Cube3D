/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meditate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:24:06 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/13 13:30:05 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	free_sprites(t_brain *b)
{
	int i;

	i = 0;
	while (i < b->map->sprites->length)
	{
		free_buff(b->map->sprites->list[i]->model);
		free_buff(b->map->sprites->list[i]->shadow);
		free(b->map->sprites->list[i++]);
	}
	free(b->map->sprites->list);
	free(b->map->sprites->column);
	free(b->map->sprites);
}

void	free_map(t_brain *b)
{
	int			i;
	t_sprite	*s;

	i = 0;
	ft_putstr(DYELO"Free Map\n");
	if (b != NULL && b->map != NULL)
	{
		free_buff(b->map->w_n);
		free_buff(b->map->w_e);
		free_buff(b->map->w_s);
		free_buff(b->map->w_w);
		free_buff(b->map->floor);
		free_buff(b->map->skybox);
		free_buff(b->map->frame);
		free_sprites(b);
		i = 0;
		while (i < b->map->height)
		{
			free(b->map->grid[i]->line);
			free(b->map->grid[i]);
			i++;
		}
		free(b->map->grid);
		check_n_free(b->map);
	}
}
