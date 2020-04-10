/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:53:12 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/10 15:53:14 by siferrar         ###   ########lyon.fr   */
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
	dprintf(1, "{ x:%6f, y:%6f }\n", p->x, p->y);
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

void	print_map_debug(t_map_line *line)
{
	int i;

	i = 0;
	while (i < line->length)
	{
		if (line->line[i] == 0)
			ft_putstr(DGREY);
		else if (line->line[i] == 1)
			ft_putstr(DCYAN);
		else if (line->line[i] == 2)
			ft_putstr(YELO);
		else if (line->line[i] > 5)
			ft_putstr(PINK); 
		if (line->line[i] == -1)
			ft_putchar(' ');
		else
			ft_putnbr(line->line[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putstr(" - ");
	ft_putnbr(line->length);
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
		print_map_debug(map->grid[y]);
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
