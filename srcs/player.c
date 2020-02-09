/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 22:24:57 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 21:07:26 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

int		init_player(t_brain *b, int pos_x)
{
	printf(DCYAN" -> Init player ");
	if ((b->player = malloc(sizeof(t_player))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER\n"RST);
		exit(0);
	}
	if ((b->player->pos = malloc(sizeof(t_point))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER POS\n"RST);
		exit(0);
	}
	if ((b->player->r_pos = malloc(sizeof(t_point))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER POS\n"RST);
		exit(0);
	}
	b->player->r_pos->x = (pos_x * b->map->bloc_size) - (b->map->bloc_size/2);
	b->player->r_pos->y = (b->map->height * b->map->bloc_size) - b->map->bloc_size/2;
	disp_point(b->player->pos);
	init_cam(b);
	b->player->move = &move;
	b->player->rot = &rotate;
	b->player->draw = &draw_player;
	b->player->ctx = b->ctx;
	b->player->speed = 3;
	b->player->angle = PI*0.75*2;
	b->player->rot_speed = (1 * PI) / 180;
	b->player->inited = 1;
	b->player->step = malloc(sizeof(t_point));
	b->player->step->x = 1;
	b->player->step->y = 1;
	b->player->brain = b;
	printf(" - OK\n");
	return (1);
}

double deg_to_rad(double angle)
{
	return ((angle * PI)/ 180);
}

double rad_to_deg(double angle)
{
	return (angle * 180.0 / PI);
}

void	draw_rays(struct s_player *p, t_ctx *ctx)
{
	double fov = deg_to_rad(90);
	int rayDist = 500;
	int nbrRay = 6;
	int i = 0;
	double cur_a = 0;

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

void	move(struct s_player *p, int dir)
{
	t_map *map;
	t_brain *b;

	b = (t_brain *)p->brain;
	map = b->map;

	if (p->r_pos->y < map->px_height)
	{
		p->r_pos->y += p->step->y * dir;
		if (p->r_pos->y < 0)
			p->r_pos->y = 0;
	}
	else
		p->r_pos->y = map->px_height - 1;

	if (p->r_pos->x < map->px_width)
	{
		p->r_pos->x += p->step->x * dir;
		if (p->r_pos->x < 0)
			p->r_pos->x = 0;
	}
	else
		p->r_pos->x = map->px_width - 1;
	p->pos->x = p->r_pos->x;
	p->pos->y = p->r_pos->y;
}

void	rotate(struct s_player *p, int dir)
{
	//double dist;

	if (dir < 0)
		p->angle -= p->rot_speed;
	else
		p->angle += p->rot_speed;
	if (p->angle > 2*PI)
		p->angle = p->angle - 2 * PI;
	if (p->angle < 0)
		p->angle = 2 * PI - p->angle;

	//dist = calc_dist(*p->pos, new_point(p->pos->x + p->speed * cos(p->angle), p->pos->y + p->speed * sin(p->angle)));

	p->step->x = (p->pos->x + p->speed * cos(p->angle)) - p->pos->x;
	ft_putint("Step->x; ", p->step->x);
	p->step->y = (p->pos->y + p->speed * sin(p->angle)) - p->pos->y;
	ft_putint("Step.y; ", p->step->y);
	printf("Angle: %f\n", rad_to_deg(p->angle));
	//p->draw(p, ctx);
}