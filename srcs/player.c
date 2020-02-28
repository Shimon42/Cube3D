/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:24:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/28 08:29:48 by siferrar         ###   ########lyon.fr   */
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
	b->player->speed = 4;
	b->player->angle = get_player_angle(angle);
	b->player->rot_speed = (2 * PI) / 180;
	b->player->step = malloc(sizeof(t_fpoint *));
	b->player->rot(b->player, 0);
	b->player->brain = b;
	b->player->as_move = 1;
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

void	side_move(struct s_player *p, int dir)
{
	t_map *map;
	t_brain *b;

	b = (t_brain *)p->brain;
	map = b->map;

	if (p->pos->y < map->px_height)
	{
		p->pos->y +=  p->speed * (sin(p->angle + (ft_inrad(90)) * dir));
		if (p->pos->y < 0)
			p->pos->y = 0;
	}
	else
		p->pos->y = map->px_height - 1;

	if (p->pos->x < map->px_width)
	{
		p->pos->x +=  p->speed * (cos(p->angle + (ft_inrad(90)) * dir));
		if (p->pos->x < 0)
			p->pos->x = 0;
	}
	else
		p->pos->x = map->px_width - 1;
	p->as_move = 1;
}

void	move(struct s_player *p, int dir)
{
	t_map *map;
	t_brain *b;

	b = (t_brain *)p->brain;
	map = b->map;

	if (p->pos->y < map->px_height)
	{
		p->pos->y += p->step->y * (float)dir;
		if (p->pos->y < 0)
			p->pos->y = 0;
	}
	else
		p->pos->y = map->px_height - 1;

	if (p->pos->x < map->px_width)
	{
		p->pos->x += p->step->x * (float)dir;
		if (p->pos->x < 0)
			p->pos->x = 0;
	}
	else
		p->pos->x = map->px_width - 1;
	p->as_move = 1;
}

void	rotate(struct s_player *p, float angle)
{
	p->angle += angle;
	if (p->angle > 2*PI)
		p->angle = p->angle - 2 * PI;
	if (p->angle <= 0)
		p->angle = 2 * PI - p->angle;

	p->step->x = (p->pos->x + p->speed * cos(p->angle)) - p->pos->x;
	//dprintf(1, "Step->x: %f \n", p->step->x);
	p->step->y = (p->pos->y + p->speed * sin(p->angle)) - p->pos->y;
	//dprintf(1, "Step->y: %f \n", p->step->y);
	//printf("Angle: %f\n", rad_to_deg(p->angle));
	p->as_move = 1;
	//p->draw(p, ctx);
}

void	jump(t_player *p, float speed)
{
	static int jumping = 0;
	t_brain *b;

	b = (t_brain *)p->brain;

	//dprintf(1, "jump: %d  -- jumpingof %f  -- z: %f\n", jumping, speed, p->z);
	if (speed > 0 && jumping == 0)
		jumping = 1;
	else if (speed < 0)
		jumping = -1;
	if (p->z > 0 && speed < 0 && jumping == -1)
	{
		p->z += speed;
		jumping = -1;
	}
	else if (jumping == -1 && p->z < 0) {
		p->z = 0;
		jumping = 0;
	}
	if (jumping && speed > 0 && p->z < b->map->bloc_size * 0.75)
		p->z += speed * jumping;
	else if (jumping)
		jumping = -1;

	if (jumping != 0)
		p->as_move = 1;
}