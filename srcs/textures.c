/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:25:10 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 12:55:08 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void init_texture(t_brain *b, char *path, t_buff **t)
{
	int fd;
	
	dprintf(1, DCYAN"	-> %s", path);
	*t = malloc(sizeof(t_buff));
	if (*t)
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
		dprintf(1, GRN" - OK\n"RST);
	}
	else
		exit_cube(NULL, 401, "Failed to malloc texture", 0);
}