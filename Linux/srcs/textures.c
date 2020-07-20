/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:25:10 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/20 16:19:50 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_texture(t_brain *b, char *path, t_buff **t)
{
	int	fd;

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
		ft_printf(GRN" - OK\n"RST);
	}
	else {
		(*t)->is_color = ft_atoi(path);
		(*t)->initied = 3;
		(*t)->img = NULL;
		(*t)->addr = NULL;
		(*t)->max_addr = 1;
		(*t)->offset = 1;
		(*t)->ratio = 1;
		(*t)->width = 1;
		(*t)->height = 1;
		(*t)->line_length = 1;
	}		
}
