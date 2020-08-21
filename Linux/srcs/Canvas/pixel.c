/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:42:08 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/21 21:41:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"
#include "../../includes/cube3d.h"

void	pixel_put(int x, int y, int color, t_buff *buff)
{
	int		addr_index;

	addr_index = (y * buff->line_length + x * buff->offset);
	if (addr_index >= 0 && addr_index < buff->max_addr)
		*(unsigned int*)(buff->addr + addr_index) = color;
}

int		pixel_get(t_buff *img, int x, int y)
{
	int		addr_index;
	int		*color;

	if (img->is_color != -1)
		return (img->is_color);
	addr_index = (y * img->line_length + x * img->offset);
	if (addr_index >= 0 && addr_index < img->max_addr)
	{
		color = (int*)(img->addr + addr_index);
		return (*color);
	}
	return (-1);
}
