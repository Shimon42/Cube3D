/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:43:45 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 23:56:59 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int get_grid(t_map *m, int x, int y)
{
	return (m->grid[y * m->width + x] - '0');
}

t_point			to_grid(t_point *p, t_map *m)
{
	t_point ret;

	ret.x = p->x / m->bloc_size;
	ret.y = p->y / m->bloc_size;
	return(ret);
}

t_point			map_scaled(t_point *p, t_map *m)
{
	t_point ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return(ret);
}

void            draw_frame(t_brain *b, int x, int y, double scale)
{
	//disp_map_s(b->map);
	//printf("x: [%d]\ny: [%d]\n", x, y);
	//printf("x: [%f]\ny: [%f]\n", (double)x, (double)y);
	b->ctx->color = 0x00FFFF;
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
	t_point p_pos;
	i = 0;
	y = 0;
	p_pos = to_grid(b->player->pos, b->map);
	while (y < b->map->height)
	{
		x = 0;
		while (x < b->map->width)
		{
			val = b->map->grid[i];
			if (val == '0')
				b->ctx->color = 0;
			else if (val == '1')
				b->ctx->color = 0x00FFFF;
			else if (val == '2')
				b->ctx->color = 0x00FF00;
			else
				b->ctx->color = 0xFF0000;
			b->ctx->rect(floor(disp_x + (x * (b->map->bloc_size * scale))),
						floor(disp_y + (y * (b->map->bloc_size * scale))),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						1,
						b->ctx);
			b->ctx->color = 0;
			b->ctx->rect(floor(disp_x + (x * (b->map->bloc_size * scale))),
						floor(disp_y + (y * (b->map->bloc_size * scale))),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						0,
						b->ctx);
			i++;
			x++;
		};
		y++;
	}
	b->ctx->color = 0xFFFF00;
	b->ctx->rect(floor(disp_x + (p_pos.x * (b->map->bloc_size * scale))),
				floor(disp_y + (p_pos.y * (b->map->bloc_size * scale))),
				b->map->bloc_size * scale,
				b->map->bloc_size * scale,
				0,
				b->ctx);
}

void	draw_minimap_rays(t_brain *b, t_point disp)
{
		t_point close_h = closest_grid_h(b->player->pos, b->map, b->player->angle);
		t_point close_v = closest_grid_v(b->player->pos, b->map, b->player->angle);
		t_point p_pos = map_scaled(b->player->pos, b->map);
		int ray_length = 500;
		close_h = map_scaled(&close_h, b->map);
		close_v = map_scaled(&close_v, b->map);
		b->ctx->color = 0xFF0000;
		b->ctx->circle(disp.x + close_h.x, disp.y + close_h.y, 3, 1, b->ctx);
		b->ctx->color = 0x0000FF;
		b->ctx->circle(disp.x + close_v.x, disp.y + close_v.y, 3, 1, b->ctx);
		b->ctx->color = 0x00FFFF;
		
		
		b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
			new_point(disp.x + p_pos.x  + ray_length * cos(b->player->angle), disp.y + p_pos.y + ray_length * sin(b->player->angle) ),
			b->ctx);

}

void			draw_player_map(t_brain *b, t_player *p, t_point m_pos)
{
	b->ctx->color = 0xFF00FF;
	b->ctx->circle(m_pos.x + (p->pos->x * b->map->scale),
					m_pos.y + (p->pos->y * b->map->scale),
					(b->map->bloc_size * 0.3) * b->map->scale,
					1,
					b->ctx);
	draw_minimap_rays(b, m_pos);
}

void			draw_minimap(t_brain *b, int x, int y, int width)
{
	double scale;

	//ft_putstr("Draw frame - ");
	scale = ((double)(width / (double)b->map->px_width)) ;
	b->map->scale = scale;
	
    draw_frame(b, x, y, scale);
	//ft_putstr("OK\n");
    draw_elems(b, x, y, scale);
	draw_player_map(b, b->player, new_point(x, y));
	
}

void			draw_fullmap(t_brain *b, double ease_val)
{
	int margin;
	double scale;
	double margin_top;
	static double ease = 0;

	if (ease_val > 0)
	{
		margin = 100;
		scale = ((double)((b->ctx->width - 2 * margin) / (double)b->map->px_width)) ;
		margin_top = (b->ctx->height - (b->map->height * b->map->bloc_size * scale)) / 2;
		draw_minimap(b, 
					margin,
					margin_top,
					(b->ctx->width - 2 * margin) * (ease));
		if (ease < 1)
			ease += ease_val;
		else
			ease = 1;
	}
	else
		ease = 0;
}