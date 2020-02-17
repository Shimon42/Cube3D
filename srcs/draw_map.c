/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 22:43:45 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 21:17:09 by siferrar    ###    #+. /#+    ###.fr     */
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
		if (need_rescale && x < m->px_width && y < m->px_height)
		{
			scaled = to_grid(x, y, m);
			x = scaled.x;
			y = scaled.y;
		}else

			//ft_putstr(RED"OUT OF GRID\n"RST);
		
			return (-1);
	//	ft_putstr(GRN"OK -> "YELO);
		//ft_putchar(m->grid[y * m->width + x]);
		//ft_putstr("\n"RST);
		return (m->grid[y * m->width + x] - '0');
	}else
	{
		//ft_putstr(RED"OUT OF GRID\n"RST);
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

t_fpoint			map_fscaled(t_fpoint *p, t_map *m)
{
	t_fpoint ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return(ret);
}

t_point			map_scaled(t_point *p, t_map *m)
{
	t_point ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return(ret);
}

void            draw_frame(t_brain *b)
{
	//disp_map_s(b->map);
	//printf("x: [%d]\ny: [%d]\n", x, y);
	//printf("x: [%f]\ny: [%f]\n", (double)x, (double)y);
	b->ctx->color = 0x000000;
    b->ctx->rect(b->map->disp.x,
                b->map->disp.y,
                b->map->bloc_size * b->map->width * b->map->scale,
                b->map->bloc_size * b->map->height * b->map->scale,
                1,
				b->ctx);
	//disp_map_s(b->map);
}

void		point_on_map(t_brain *b, int x, int y, int color)
{
	t_point p;
	
	p = new_point(x, y);
	p = map_scaled(&p, b->map);
	b->ctx->color = color;
	b->ctx->circle(b->map->disp.x + p.x, b->map->disp.y + p.y, (b->map->bloc_size * 0.06) * b->map->scale, 1, b->ctx);
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
			else if (val == 'N' || val == 'E' || val == 'S' || val == 'W')
			{
				b->ctx->color = 0xFF00FF;
			} else
				b->ctx->color = 0xFF0000;

			b->ctx->rect(floor(disp_x + (x * (b->map->bloc_size * scale))),
						floor(disp_y + (y * (b->map->bloc_size * scale))),
						b->map->bloc_size * scale,
						b->map->bloc_size * scale,
						1,
						b->ctx);
			b->ctx->color = 0x333333;
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

void	line_on_map(t_brain *b, t_point p1, t_point p2)
{
	p1 = map_scaled(&p1, b->map);
	p2 = map_scaled(&p2, b->map);
	b->ctx->line(new_point(b->map->disp.x + p1.x, b->map->disp.y + p1.y),
			new_point(b->map->disp.x + p2.x, b->map->disp.y + p2.y),
			b->ctx);	
}

void	draw_minimap_closest(t_brain *b, t_point disp, double angle)
{
		int color = b->ctx->color;
		t_fpoint close_h = closest_grid_h(b->player->pos, b->map, angle);
		t_fpoint close_v = closest_grid_v(b->player->pos, b->map, angle);
		t_point p_pos = map_scaled(b->player->pos, b->map);
		t_detect wall;

		//int ray_length = 500;
		close_h = map_fscaled(&close_h, b->map);
		close_v = map_fscaled(&close_v, b->map);

		wall = dist_to_wall(b, b->player->pos, angle);
		b->ctx->color = color;
		b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
			new_point(disp.x + p_pos.x  + (wall.dist * b->map->scale) * cos(angle), disp.y + p_pos.y + (wall.dist * b->map->scale) * sin(angle) ),
			b->ctx);	
		b->ctx->color = 0xFF0000; // RED H
		b->ctx->circle(disp.x + close_h.x, disp.y + close_h.y, (b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF; // YELLO V
		b->ctx->circle(disp.x + close_v.x, disp.y + close_v.y, (b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF;
}


void	draw_minimap_rays(t_brain *b, t_point disp)
{
		t_fpoint close_h = closest_wall_h(b, b->player->pos, b->player->angle);
		t_fpoint close_v = closest_wall_v(b, b->player->pos, b->player->angle);
		//t_point p_pos = map_scaled(b->player->pos, b->map);
		//int ray_length = 500;

		close_h = map_fscaled(&close_h, b->map);
		close_v = map_fscaled(&close_v, b->map);

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
	
	//draw_minimap_closest(b, m_pos, p->angle);
	//b->ctx->color = 0xFF0000;
	//draw_minimap_closest(b, m_pos, to_360(p->angle - p->cam->fov / 2));
	//b->ctx->color = 0x00FF00;
	//draw_minimap_closest(b, m_pos, p->angle + p->cam->fov / 2);
	//draw_minimap_rays(b, m_pos);
}

void	draw_fov_map(t_brain *b, t_ctx *c)
{
	t_detect wall;
	double dist;
	double cur_col;
	double col_step;
	double cur_angle;

	cur_col = 0;
	col_step = b->player->cam->fov/ c->width;
	//printf("START DRAW WALLS\n");
	while (cur_col < c->width)
	{
		cur_angle = b->player->angle - (b->player->cam->fov / 2) + (col_step * cur_col);

		wall = dist_to_wall(b, b->player->pos, cur_angle);
		dist = wall.dist;

		b->ctx->color = 0xFF00FF;
		line_on_map(b,
			*b->player->pos,
			new_point(b->player->pos->x + (wall.dist) * cos(cur_angle), b->player->pos->y + (wall.dist) * sin(cur_angle)));	
		if (cur_col < c->width / 2)
			dist = dist * cos(-(b->player->angle - cur_angle));
		else
			dist = dist * cos ((b->player->angle - cur_angle));
		cur_col+=c->width / 10;
	}
}

void			draw_minimap(t_brain *b, int x, int y, int width)
{
	double scale;

	//ft_putstr("Draw frame - ");
	scale = ((double)(width / (double)b->map->px_width)) ;
	b->map->scale = scale;
	b->map->disp.x = x;
	b->map->disp.y = y;
	
    draw_frame(b);
	//ft_putstr("OK\n");
    draw_elems(b, x, y, scale);
	draw_player_map(b, b->player, new_point(x, y));
	//draw_fov_map(b, b->ctx);
}

void			draw_fullmap(t_brain *b, double ease_val)
{
	int margin;
	double scale;
	double margin_top;
	static double ease = 0;

	if (ease_val > 0)
	{
		margin = 100 * b->map->scale;
		scale = ((double)((b->ctx->width - 2 * margin) / (double)b->map->px_width)) ;
		margin_top = (b->ctx->height - (b->map->height * b->map->bloc_size * scale)) / 2;
		draw_minimap(b, 
					margin,
					margin_top,
					(b->ctx->width - 2 * margin) * (ease));
		if (ease < 1 && ease + ease_val < 1)
			ease += ease_val;
		else
			ease = 1;
	}
	else
		ease = 0;
}