/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simeon <simeon@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:43:45 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 15:38:05 by simeon      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"


void            draw_frame(t_brain *b, int x, int y, double scale)
{
	//disp_map_s(b->map);
	//printf("x: [%d]\ny: [%d]\n", x, y);
	//printf("x: [%f]\ny: [%f]\n", (double)x, (double)y);
    b->ctx->rect(x,
                y,
                b->map->bloc_size * b->map->width * scale,
                b->map->bloc_size * b->map->height * scale,
                0,
				b->ctx);
	//disp_map_s(b->map);
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
			else
				b->ctx->color = 0xFF0000;
			b->ctx->rect(floor(disp_x + (x * b->map->bloc_size * scale)),
						floor(disp_y + (y * b->map->bloc_size * scale)),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						1,
						b->ctx);
			b->ctx->color = 0x999999;
			b->ctx->rect(floor(disp_x + (x * b->map->bloc_size * scale)),
						floor(disp_y + (y * b->map->bloc_size * scale)),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						0,
						b->ctx);
			i++;
			x++;
		};
		y++;
	}
	//ft_putstr("Draw Elems ok\n");
}

void			draw_player_map(t_brain *b, t_player *p, t_point m_pos)
{
	b->ctx->color = 0xFF00FF;
	b->ctx->circle(m_pos.x + (p->pos->x + (b->map->bloc_size * b->map->scale)) + (b->map->bloc_size * b->map->scale)/2,
					m_pos.y + (p->pos->y + (b->map->bloc_size * b->map->scale)) + (b->map->bloc_size * b->map->scale)/2,
					2 * b->map->scale,
					1,
					b->ctx);
}

void			draw_minimap(t_brain *b, int x, int y, double scale)
{
	//ft_putstr("Draw frame - ");
	b->map->scale = scale;
    draw_frame(b, x, y, scale);

	//ft_putstr("OK\n");
    draw_elems(b, x, y, scale);
	draw_player_map(b, b->player, new_point(x, y));
}

void			draw_fullmap(t_brain *b, double scale)
{
	draw_minimap(b, 
				(b->ctx->width - (b->map->width * b->map->bloc_size *  scale))/2,
				(b->ctx->height - (b->map->height * b->map->bloc_size * scale))/2,
				scale);
}