/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:43:45 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:22:05 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int get_grid(t_map *m, int x, int y, int need_rescale)
{
	t_point scaled;

	/*ft_putstr("Wanting val of grid [");
	ft_putnbr(x);
	ft_putstr("][");
	ft_putnbr(y);
	ft_putstr("] - ");*/
	if (x > 0 && y > 0)
	{
		if (need_rescale)
		{
			scaled = to_grid(x, y, m);
			x = scaled.x;
			y = scaled.y;
		}
	//	ft_putstr(GRN"OK -> "YELO);
		//ft_putchar(m->grid[y * m->width + x]);
		//ft_putstr("\n"RST);
		return (m->grid[y * m->width + x] - '0');
	}else
	{
		//ft_putstr(RED"BAD\n"RST);
		return (-1);
	}
}

t_point			to_grid(int x, int y, t_map *m)
{
	t_point ret;

	
	ret.x = x / m->bloc_size;
	ret.y = y / m->bloc_size;
	//ft_putstr("TOGRID[");
	//ft_putnbr(ret.x);
	//ft_putstr("][");
	//ft_putnbr(ret.y);
	//ft_putstr("] \n");
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
	b->ctx->color = 0x000000;
    b->ctx->rect(x,
                y,
                b->map->bloc_size * b->map->width * scale,
                b->map->bloc_size * b->map->height * scale,
                1,
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
	p_pos = to_grid(b->player->pos->x, b->player->pos->y, b->map);
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

void	draw_minimap_closest(t_brain *b, t_point disp)
{
		t_point close_h = closest_grid_h(b->player->pos, b->map, b->player->angle);
		t_point close_v = closest_grid_v(b->player->pos, b->map, b->player->angle);
		t_point p_pos = map_scaled(b->player->pos, b->map);
		int ray_length = 500;
		close_h = map_scaled(&close_h, b->map);
		close_v = map_scaled(&close_v, b->map);

		b->ctx->color = 0xFFFFFF;
		b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
			new_point(disp.x + p_pos.x  + ray_length * cos(b->player->angle), disp.y + p_pos.y + ray_length * sin(b->player->angle) ),
			b->ctx);

		b->ctx->color = 0xFF0000;
		b->ctx->circle(disp.x + close_h.x, disp.y + close_h.y, (b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF;
		b->ctx->circle(disp.x + close_v.x, disp.y + close_v.y, (b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF;
}


void	draw_minimap_rays(t_brain *b, t_point disp)
{
		t_point close_h = closest_wall_h(b, b->player->pos, b->player->angle);
		t_point close_v = closest_wall_v(b, b->player->pos, b->player->angle);
		//t_point p_pos = map_scaled(b->player->pos, b->map);
		//int ray_length = 500;

		close_h = map_scaled(&close_h, b->map);
		close_v = map_scaled(&close_v, b->map);

		b->ctx->color = 0xFFFF00;
		b->ctx->circle(disp.x + close_h.x, disp.y + close_h.y, (b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
		//b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
		//	new_point(disp.x + close_h.x , disp.y + close_h.y ),
		//	b->ctx);

		b->ctx->color = 0xFF00FF;
		b->ctx->circle(disp.x + close_v.x, disp.y + close_v.y, (b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
		//b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
		//	new_point(disp.x + close_v.x , disp.y + close_v.y ),
		//	b->ctx);

}

void			draw_player_map(t_brain *b, t_player *p, t_point m_pos)
{
	b->ctx->color = 0xFFFFFF;
	b->ctx->circle(m_pos.x + (p->pos->x * b->map->scale),
					m_pos.y + (p->pos->y * b->map->scale),
					(b->map->bloc_size * 0.1) * b->map->scale,
					1,
					b->ctx);
	draw_minimap_closest(b, m_pos);
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