/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:53:12 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/16 09:33:50 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	disp_keys(t_brain *b)
{
	int i;

	i = 0;
	while (i < 10)
	{
		ft_putnbr(b->keys[i]);
		if (i < 9)
			ft_putstr(", ");
		i++;
	}
	ft_putchar('\n');
}

void	disp_point(t_fpoint *p)
{
	printf("{ x:%6f, y:%6f }\n", p->x, p->y);
}

void	disp_map_s(t_map *m)
{
	printf("\nMap:\n\tHeight: [%d]\n\tWidth: [%d]\n\tBloc Size: [%d]\n\tScale: [%f]\n", m->width, m->height, m->bloc_size, m->scale);
}

void	disp_buff(t_buff *b)
{
	if (b->img)
		printf("\nimg: set\n");
	else
		printf(RED"\nNO IMG\n"RST);
	printf("addr: [%s]\n", b->addr);
	printf("bit/pixel: [%d]\n", b->bits_per_pixel);
	printf("line_len: [%d]\n", b->line_length);
	printf("endian: [%d]\n", b->endian);
}

void	print_player_debug(t_brain *b)
{
	b->ctx->color = 0x88000000;
	b->ctx->rect(10,10, 200,100, 1, b->ctx);
	b->ctx->color = 0xFFFFFF;
	b->ctx->text("PosX: ", 12, 12, b->ctx);
	b->ctx->text(ft_itoa(b->player->pos->x), 65, 12, b->ctx);
}

void	print_map_debug(char *line)
{
	while (*line)
	{
		if (*line == '0')
			ft_putstr(DGREY);
		else if (*line == '1')
			ft_putstr(DCYAN);
		else if (*line == '2')
			ft_putstr(YELO);
		else if (*line == 'N')
			ft_putstr(PINK); 
		ft_putchar(*line++);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	print_map_grid(t_map *map)
{
	int x;
	int y;
	int i;
	char val;

	i = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		print_map_debug(map->grid[y]->line);
		y++;
	}
}

void	disp_brain(t_brain *b)
{
    printf(CYAN"┌────────────────────────────\n");
    printf("|----------- BRAIN ----------\n");
    printf("|\n");
	printf("|\tINITED: %d\n", b->inited);
    printf("────────────────────────────"RST"\n");
}
