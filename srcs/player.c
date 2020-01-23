/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 22:24:57 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 19:16:05 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int		init_player(t_brain *b, int pos_x)
{
	printf(DCYAN" -> Init player ");
	if ((b->player = malloc(sizeof(t_player *))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER\n"RST);
		exit(0);
	}
	if ((b->player->pos = malloc(sizeof(t_point *))) == NULL)
	{
		ft_putstr(RED"FAILED TO MALLOC PLAYER POS\n"RST);
		exit(0);
	}
	b->player->pos->x = (pos_x * b->map->bloc_size) - (b->map->bloc_size/2);
	b->player->pos->y = (b->map->height * b->map->bloc_size) - b->map->bloc_size/2;
	disp_point(b->player->pos);
	printf(" - OK\n");
	b->player->move = &move;
	b->player->speed = 1;
	b->player->angle = 0;
	return (1);
}

void	move(struct s_player *p, t_ctx *ctx)
{
	p->pos->x = p->pos->x + p->speed * cos(p->angle);
	p->pos->y = p->pos->y + p->speed * sin(p->angle);
	ctx->circle(p->pos->x, p->pos->y, 5, 1, ctx);
}