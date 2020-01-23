/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 22:24:57 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:28:49 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int		init_player(t_brain *b, int pos_x)
{
	printf("INIT PLAYER\n");
	b->player = malloc(sizeof(t_player*));
	b->player->pos = malloc(sizeof(t_point *));

	b->player->pos->x = (pos_x * b->map->bloc_size) - b->map->bloc_size/2;
	b->player->pos->y = (b->map->height * b->map->bloc_size) - b->map->bloc_size/2;
	printf("INIT PLAYER OK\n");
	return (1);
}