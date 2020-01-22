/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:43:45 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 18:09:56 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"


void            draw_frame(t_brain *b, int x, int y, double scale)
{
    t_map *map;

    map = b->map;
    b->ctx->rect(b->ctx,
                x,
                y,
                map->bloc_size * map->width * scale,
                map->bloc_size * map->height * scale,
                0);
}

void		draw_elems(t_brain *b, int disp_x, int disp_y, double scale)
{
	int y;
	int x;
	int i;
	char val;
	
	i = 0;
	y = 0;
	while (y < b->map->height)
	{
		x = 0;
		while (x < b->map->width)
		{
			val = b->map->grid[i];
			if (val == '0')
				b->ctx->color = 0x555555;
			else if (val == '1')
				b->ctx->color = 0x00FFFF;
			else if (val == '2')
				b->ctx->color = 0x00FF00;
			else if (val == 'N')
				b->ctx->color = 0x00DDDD;
			else
				b->ctx->color = 0xFF0000;
			b->ctx->rect(b->ctx,
						disp_x + (x * b->map->bloc_size * scale),
						disp_y + (y * b->map->bloc_size * scale),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						1);
			i++;
			x++;
		};
		y++;
	}
}

void			draw_minimap(t_brain *b, int x, int y, double scale)
{
    t_map *map;

    map = b->map;
    draw_frame(b, x, y, scale);
    draw_elems(b, x, y, scale);
}