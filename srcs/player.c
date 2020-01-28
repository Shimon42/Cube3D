/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 22:24:57 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 23:19:06 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
	b->player->pos->x = (pos_x * b->map->bloc_size) - (b->map->bloc_size/2);
	b->player->pos->y = (b->map->height * b->map->bloc_size) - b->map->bloc_size/2;
	disp_point(b->player->pos);
	b->player->move = &move;
	b->player->rot = &rotate;
	b->player->draw = &draw_player;
	b->player->ctx = b->ctx;
	b->player->speed = 5;
	b->player->angle = 0;
	b->player->rot_speed = (5 * PI) / 180;
	b->player->inited = 1;
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
	if (p->pos->y < p->ctx->height)
		p->pos->y += round(((p->speed * sin(deg_to_rad(p->angle))) * dir));
	else
		p->pos->y = p->ctx->height - 5;
	if (p->pos->x < p->ctx->width)
		p->pos->x += round(((p->speed * cos(deg_to_rad(p->angle))) * dir));
	else
		p->pos->x = p->ctx->width - 5;
}

void	rotate(struct s_player *p, int dir)
{

	if (dir < 0)
		p->angle -= p->rot_speed;
	else
		p->angle += p->rot_speed;
	if (p->angle > 2*PI)
		p->angle = p->angle - 2 * PI;
	if (p->angle < 0)
		p->angle = 2 * PI - p->angle;
	printf("Angle: %f\n", rad_to_deg(p->angle));
	//p->draw(p, ctx);
}