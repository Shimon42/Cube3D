/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:25:10 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/17 11:37:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_color(t_buff *t, char *path)
{
	ft_printf(IPINK"\nPATH IS COLOR %s => %d\n"RST, path, ft_atoi(path));
	t->is_color = ft_atoi(path);
	t->initied = 3;
	t->img = NULL;
	t->addr = NULL;
	t->max_addr = 1;
	t->offset = 1;
	t->ratio = 1;
	t->width = 1;
	t->height = 1;
	t->line_length = 1;
}

void	init_texture(t_brain *b, char *path, t_buff **t)
{
	ft_printf(DCYAN"	-> %s", path);
	if ((*t = malloc(sizeof(t_buff))) == NULL)
		exit_cube(NULL, 401, "Failed to malloc texture", 0);
	if (ft_ext_check(path, ".xpm"))
	{
		(*t)->initied = 1;
		(*t)->img = mlx_xpm_file_to_image(b->ctx->mlx_ptr, path,
												&(*t)->width, &(*t)->height);
		if (!(*t)->img)
			exit_cube(NULL, 404, path, 0);
		(*t)->initied = 2;
		(*t)->addr = mlx_get_data_addr((*t)->img, &(*t)->bits_per_pixel,
									&(*t)->line_length,
									&(*t)->endian);
		(*t)->max_addr = (*t)->line_length * (*t)->height;
		(*t)->offset = (*t)->bits_per_pixel / 8;
		(*t)->ratio = (*t)->width / b->map->bloc_size;
		(*t)->initied = 3;
		(*t)->is_color = -1;
		ft_printf(GRN" - OK\n"RST);
	}
	else
		init_color(*t, path);
}
