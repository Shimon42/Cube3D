/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meditate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:24:06 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/06 12:03:27 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	free_sprites(t_brain *b)
{
	int i;

	i = 0;
	while (i < b->map->sprites->length)
	{
		if (b->map->sprites->list[i]->shadow != NULL)
		{
			free_buff(b, b->map->sprites->list[i]->model);
			free_buff(b, b->map->sprites->list[i]->shadow);
		}
		free(b->map->sprites->list[i++]);
	}
	free(b->map->sprites->list);
	free(b->map->sprites->column);
	free(b->map->sprites);
	if (b->map->default_spr != NULL)
		free_buff(b, b->map->default_spr);
}

void	free_textures(t_brain *b)
{
	ft_putstr(DGRN"Free Textures\n");
	free_buff(b, b->map->w_n);
	free_buff(b, b->map->w_e);
	free_buff(b, b->map->w_s);
	free_buff(b, b->map->w_w);
	free_buff(b, b->map->floor);
	free_buff(b, b->map->skybox);
}

void	free_map(t_brain *b)
{
	int			i;

	i = 0;
	ft_putstr(YELO"Free Map\n");
	if (b != NULL && b->map != NULL)
	{
		free_textures(b);
		mlx_destroy_image(b->ctx->mlx_ptr, b->map->frame->img);
		b->map->frame->img = NULL;
		free_buff(b, b->map->frame);
		while (i < b->map->height)
		{
			free(b->map->grid[i]->line);
			free(b->map->grid[i]);
			i++;
		}
		free(b->map->grid);
		ft_putstr(CYAN"Free Sprites\n");
		free_sprites(b);
		check_n_free(b->map);
	}
}
