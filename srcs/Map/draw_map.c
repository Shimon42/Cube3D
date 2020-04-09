/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:43:45 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/09 19:19:59 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cube3d.h"

int get_grid(t_map *m, int x, int y, int need_rescale)
{
	t_fpoint scaled;
	int val;
	
	if (x >= 0 && y >= 0)
	{
		if (need_rescale)
		{
			if (x < m->px_width && y < m->px_height)
			{
				scaled = to_grid(x, y, m);
				x = scaled.x;
				y = scaled.y;
			} else 
				return (-1);
		}
		if (y < m->height && x < m->grid[y]->length)
		{
			val = m->grid[y]->line[x];
			return (val);
		}
	}
	return (-1);
}

t_fpoint			to_grid(int x, int y, t_map *m)
{
	t_fpoint ret;

	
	ret.x = x / m->bloc_size;
	ret.y = y / m->bloc_size;
	return(ret);
}

t_fpoint			map_fscaled(t_fpoint *p, t_map *m)
{
	t_fpoint ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return(ret);
}

t_fpoint			map_scaled(t_fpoint *p, t_map *m)
{
	t_fpoint ret;

	ret.x = p->x * m->scale;
	ret.y = p->y * m->scale;
	return(ret);
}

void            draw_frame(t_brain *b)
{
	b->ctx->color = 0x000000;
    b->ctx->rect(b->map->disp.x,
                b->map->disp.y,
                b->map->bloc_size * b->map->width * b->map->scale,
                b->map->bloc_size * b->map->height * b->map->scale,
                1,
				b->ctx);
}

void		point_on_map(t_brain *b, int x, int y, int color)
{
	t_fpoint p;
	
	p = new_point(x, y);
	p = map_scaled(&p, b->map);
	b->ctx->color = color;
	b->ctx->circle(b->map->disp.x + p.x, b->map->disp.y + p.y,
						(b->map->bloc_size * 0.06) * b->map->scale, 1, b->ctx);
}

void		draw_elems(t_brain *b, int disp_x, int disp_y, float scale)
{
	int y;
	int x;
	int val;
	t_fpoint p_pos;

	y = 0;
	p_pos = to_grid(b->player->pos->x, b->player->pos->y, b->map);
	while (y < b->map->height)
	{
		x = 0;
		while (x < b->map->width)
		{
			val = get_grid(b->map, x, y, 0);
			if (val >= 0)
			{
				if (val == 0)
					b->ctx->color = 0;
				else if (val == 1)
					b->ctx->color = 0x00FFFF;
				else if (val == 2)
					b->ctx->color = 0x00FF00;
				else if (val == 'N' || val == 'E' || val == 'S' || val == 'W')
				{
					b->ctx->color = 0xFF00FF;
				} else
					b->ctx->color = 0xFF0000;
				b->ctx->rect((disp_x + (x * (b->map->bloc_size * scale))),
							disp_y + (y * (b->map->bloc_size * scale)),
							b->map->bloc_size * scale,
							b->map->bloc_size * scale,
							1,
							b->ctx);
				if (b->map->scale > 0.1)
				{
					b->ctx->color = 0x222222;
					b->ctx->rect(floor(disp_x + (x * (b->map->bloc_size * scale))),
								floor(disp_y + (y * (b->map->bloc_size * scale))),
								b->map->bloc_size * scale,
								b->map->bloc_size * scale,
								0,
								b->ctx);
				}
			}
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

void	line_on_map(t_brain *b, t_fpoint p1, t_fpoint p2)
{
	p1 = map_scaled(&p1, b->map);
	p2 = map_scaled(&p2, b->map);
	b->ctx->line(new_point(b->map->disp.x + p1.x, b->map->disp.y + p1.y),
			new_point(b->map->disp.x + p2.x, b->map->disp.y + p2.y),
			b->ctx);	
}

void	draw_minimap_closest(t_brain *b, t_fpoint disp, float angle)
{
		int color = b->ctx->color;
		t_fpoint close_h = closest_grid_h(b->player->pos, b->map, angle);
		t_fpoint close_v = closest_grid_v(b->player->pos, b->map, angle);
		t_fpoint p_pos = map_scaled(b->player->pos, b->map);
		t_detect wall;

		close_h = map_fscaled(&close_h, b->map);
		close_v = map_fscaled(&close_v, b->map);
		wall = dist_to_wall(b, b->player->pos, angle);
		b->ctx->color = color;
		b->ctx->line(new_point(disp.x + p_pos.x, disp.y + p_pos.y),
		new_point(disp.x + p_pos.x + (wall.dist * b->map->scale) * cos(angle),
		disp.y + p_pos.y + (wall.dist * b->map->scale) * sin(angle)),
			b->ctx);	
		b->ctx->color = 0xFF0000; // RED H
		b->ctx->circle(disp.x + close_h.x, disp.y + close_h.y,
						(b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF; // YELLO V
		b->ctx->circle(disp.x + close_v.x, disp.y + close_v.y,
						(b->map->bloc_size * 0.08) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0x00FFFF;
}


void	draw_minimap_rays(t_brain *b, t_fpoint disp)
{
		t_detect close_h = closest_wall_h(b, b->player->pos, b->player->angle);
		t_detect close_v = closest_wall_v(b, b->player->pos, b->player->angle);

		close_h.hit = map_fscaled(&close_h.hit, b->map);
		close_v.hit = map_fscaled(&close_v.hit, b->map);
		b->ctx->color = 0xFFFF00;
		b->ctx->circle(disp.x + close_h.hit.x, disp.y + close_h.hit.y,
						(b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
		b->ctx->color = 0xFF00FF;
		b->ctx->circle(disp.x + close_v.hit.x, disp.y + close_v.hit.y,
						(b->map->bloc_size * 0.1) * b->map->scale, 1, b->ctx);
}

void			draw_player_map(t_brain *b, t_player *p, t_fpoint m_pos)
{
	b->ctx->color = 0xFFFFFF;
	b->ctx->circle(m_pos.x + (p->pos->x * b->map->scale),
					m_pos.y + (p->pos->y * b->map->scale),
					(b->map->bloc_size * 0.1) * b->map->scale,
					1,
					b->ctx);
	
	draw_minimap_closest(b, m_pos, p->angle);
	b->ctx->color = 0xFF0000;
	draw_minimap_closest(b, m_pos, to_360(p->angle - p->cam->fov / 2));
	b->ctx->color = 0x00FF00;
	draw_minimap_closest(b, m_pos, p->angle + p->cam->fov / 2);
}

void	draw_fov_map(t_brain *b, t_ctx *c)
{
	t_detect wall;
	float dist;
	float cur_col;
	float col_step;
	float cur_angle;

	cur_col = 0;
	col_step = b->player->cam->fov/ c->width;
	while (cur_col < c->width)
	{
		cur_angle = b->player->angle - (b->player->cam->fov / 2) +
														(col_step * cur_col);
		wall = dist_to_wall(b, b->player->pos, cur_angle);
		dist = wall.dist;
		b->ctx->color = 0xFF00FF;
		line_on_map(b,
			*b->player->pos,
			new_point(b->player->pos->x + (wall.dist) * cos(cur_angle),
							b->player->pos->y + (wall.dist) * sin(cur_angle)));	
		if (cur_col < c->width / 2)
			dist = dist * cos(-(b->player->angle - cur_angle));
		else
			dist = dist * cos ((b->player->angle - cur_angle));
		cur_col+=c->width / 10;
	}
}

void			draw_minimap(t_brain *b, int x, int y, int width)
{
	float scale;

	b->ctx->cur_buff = b->map->frame;
	scale = ((float)(width / (float)b->map->px_width));
	if (b->map->px_height * scale > b->ctx->height)
	{
		scale = ((float)((b->ctx->height - 2 *
						(100 * b->map->scale)) / (float)b->map->px_height));
		x = (b->ctx->width - (b->map->width * b->map->bloc_size * scale)) / 2;
		y = (b->ctx->height - (b->map->height * b->map->bloc_size * scale)) / 2;
	}
	b->map->scale = scale;
	b->map->disp.x = floor(x);
	b->map->disp.y = floor(y);
   // draw_frame(b);
    draw_elems(b, x, y, scale);
	draw_player_map(b, b->player, new_point(x, y));
	//draw_fov_map(b, b->ctx);
}

void			draw_fullmap(t_brain *b, float ease_val)
{
	int margin;
	float scale;
	float margin_top;
	static float ease = 0;

	if (ease_val > 0)
	{
		margin = 100 * b->map->scale;
		scale = ((float)((b->ctx->width - 2 * margin) / (float)b->map->px_width));
		if (b->map->px_width * scale > b->ctx->width)
			scale = ((float)((b->ctx->height - 2 * margin) / (float)b->map->px_height));
		b->map->scale = scale;
		margin_top = (b->ctx->height - (b->map->height * b->map->bloc_size * scale)) / 2;
		draw_minimap(b, 
					margin,
					margin_top,
					(b->ctx->width - 2 * margin) * (ease));
		if (ease < 1 && ease + ease_val <= 1)
		{
			ease += ease_val;
			b->player->as_move = 1;
		} else if (b->player->as_move == 0 && ease == 1)
		{
			b->player->as_move = 1;
			ease = 1.000001;
		}else if (ease != 1 && ease != 1.000001)
		{
			ease = 1;
			b->player->as_move = 1;
		}
	}
	else {
		if (ease != 0)
			b->player->as_move = 1;
		else
			b->player->as_move = 0;
		ease = 0;
	}
}