/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:24:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/09 09:23:39 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cube3d.h"

int		init_cam(t_brain *b)
{
	t_camera *cam;

	b->player->cam = malloc(sizeof(t_camera));
	cam = b->player->cam;
	cam->fov = ft_inrad(60);
	cam->proj_size.x = b->ctx->width;
	cam->proj_size.y = b->ctx->height;
	cam->proj_dist = (cam->proj_size.x / 2) / tan(cam->fov / 2);
	return (1);
}

float get_player_angle(char dir)
{
	if (dir == 'N')
		return (2 * PI * 0.75);
	if (dir == 'E')
		return (0);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	ft_putstr(RED"WRONG DIR\n");
	return (0);
}

int		init_player(t_brain *b, int pos_x, char angle)
{
	printf(DCYAN"	-> Init player at ");
	if ((b->player = malloc(sizeof(t_player))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER\n"RST);
		exit(0);
	}
	if ((b->player->pos = malloc(sizeof(t_fpoint))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER POS\n"RST);
		exit(0);
	}
	b->player->pos->x = ((pos_x + 1) * b->map->bloc_size) - (b->map->bloc_size/2);
	b->player->pos->y = (b->map->height * b->map->bloc_size) - b->map->bloc_size/2;
	disp_point(b->player->pos);
	ft_putstr("	-> Init Cam - ");
	init_cam(b);
	ft_putstr(DGRN"OK\n");
	b->player->move = &move;
	b->player->sidemove = &side_move;
	b->player->rot = &rotate;
	b->player->jump = &jump;
	b->player->draw = &draw_player;
	b->player->ctx = b->ctx;
	b->player->speed = b->map->bloc_size * 0.12;
	b->player->angle = get_player_angle(angle);
	b->player->rot_speed = (2 * PI) / 180;
	b->player->step = malloc(sizeof(t_fpoint *));
	b->player->rot(b->player, 0);
	b->player->brain = b;
	b->player->as_move = 1;
	b->player->bobbing = 1;
	b->player->jumping = 0;
	b->player->inited = 1;
	printf(GRN"Player init - "DGRN"OK\n"RST);
	return (1);
}

float deg_to_rad(float angle)
{
	return ((angle * PI)/ 180);
}

float rad_to_deg(float angle)
{
	return (angle * 180.0 / PI);
}

void	draw_rays(struct s_player *p, t_ctx *ctx)
{
	float fov = deg_to_rad(90);
	int rayDist = 500;
	int nbrRay = 6;
	int i = 0;
	float cur_a = 0;

	while (i < nbrRay/2 + 1)
	{
		ctx->line(new_point(p->pos->x, p->pos->y),
			new_point(p->pos->x + rayDist * cos(p->angle - cur_a), p->pos->y + rayDist * sin(p->angle - cur_a)),
			ctx);
		ctx->line(new_point(p->pos->x, p->pos->y),
			new_point(p->pos->x + rayDist * cos(p->angle + cur_a), p->pos->y + rayDist * sin(p->angle + cur_a)),
			ctx);
		cur_a += (fov/(nbrRay));
		i++;
	}
}

void	draw_player(struct s_player *p, t_ctx *ctx)
{
	ctx->circle(p->pos->x, p->pos->y, 5, 1, ctx);
	draw_rays(p, ctx);
}

void	bobbing(t_player *p)
{
	float step;
	float bob_height = 4;

	step = 1;
	if (p->jumping == 0)
	{
		if (p->bobbing == 1)
		{
			p->z += step;
			if (p->z > bob_height)
			{
				p->bobbing = -1;
				p->z = bob_height;
			}
		} else {
			p->z -= step;
			if (p->z <= 0)
			{
				p->bobbing = 1;
				p->z = 0;
			}
		}
	}
}

void	side_move(struct s_player *p, int dir)
{
	t_map *m;
	t_brain *b;

	b = (t_brain *)p->brain;
	m = b->map;
	if (get_grid(m, p->pos->x + p->speed * (cos(p->angle + (ft_inrad(90)) * dir)), p->pos->y, 1) != 1)
		p->pos->x += p->speed * (cos(p->angle + (ft_inrad(90)) * dir));
	if (get_grid(m, p->pos->x, p->pos->y + p->speed * (sin(p->angle + (ft_inrad(90)) * dir)), 1) != 1)
		p->pos->y += p->speed * (sin(p->angle + (ft_inrad(90)) * dir));
	p->as_move = 1;
	if (is_key_pressed(b, 13) == -1 && is_key_pressed(b, 1) == -1)
		bobbing(p);
}

void	move(struct s_player *p, int dir)
{
	t_map *m;
	t_brain *b;

	b = (t_brain *)p->brain;
	m = b->map;

	if (get_grid(m, p->pos->x + p->step->x * dir, p->pos->y, 1) != 1)
		p->pos->x += p->step->x * dir;
	if (get_grid(m, p->pos->x, p->pos->y + p->step->y * dir, 1) != 1)
		p->pos->y += p->step->y * dir;
	p->as_move = 1;
	bobbing(p);
}

void	rotate(struct s_player *p, float angle)
{
	p->angle += angle;
	if (p->angle > 2 * PI)
		p->angle = p->angle - 2 * PI;
	else if (p->angle <= 0)
		p->angle = 2 * PI - p->angle;
	p->step->x = (p->pos->x + p->speed * cos(p->angle)) - p->pos->x;
	p->step->y = (p->pos->y + p->speed * sin(p->angle)) - p->pos->y;
	p->as_move = 1;
}

void	jump(t_player *p, float speed)
{
	double jump_h;
	t_brain *b;

	b = (t_brain *)p->brain;
	jump_h = (double)b->map->bloc_size;

	if (speed > 0 && p->jumping == 0)
		p->jumping = 1;

	
	if (p->jumping != 0)
	{
		if (p->z < jump_h || (p->jumping == -1 && speed < 0))
			p->z += speed * p->jumping;
		else if (p->jumping == 1)
		{
			p->z = jump_h - 0.1;
			p->jumping = -1;
		}
		if (p->z < 0)
		{
			p->jumping = 0;
			p->z = 0;
		}
	}
	b->player->as_move = 1;
}