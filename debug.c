/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simeon <simeon@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 15:53:12 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 15:45:25 by simeon      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	disp_point(t_point *p)
{
	printf("{ x:%6d, y:%6d }\n", p->x, p->y);
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

void print_player_debug(t_brain *b)
{
	b->ctx->color = 0x88000000;
	b->ctx->rect(10,10, 200,100, 1, b->ctx);
	b->ctx->color = 0xFFFFFF;
	b->ctx->text("PosX: ", 12, 12, b->ctx);

}

void print_map_debug(char *line)
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
	}
	ft_putchar('\n');
}

void		print_map_grid(t_map *map)
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
		while (x < map->width)
		{
			val = map->grid[i];
			if (val == '0')
				ft_putstr(DGREY);
			else if (val == '1')
				ft_putstr(DCYAN);
			else if (val == '2')
				ft_putstr(YELO);
			else if (val == 'N')
				ft_putstr(PINK);
			else
				ft_putstr(RED);
			ft_putchar(val);
			if (x++ < map->width)
				ft_putchar(' ');
			i++;
		};
		ft_putchar('\n');
		y++;
	}
}

/*
void disp_brain(t_brain *b)
{
    t_param **params;

    params = &(b->params);
    printf(CYAN"┌────────────────────────────\n");
    printf("|----------- BRAIN ----------\n");
    printf("|\n");
    printf(YELO"|\tParams:\n");
    while (*params != NULL)
    {
		disp_param(*params);
        params = &((*params)->next);
    }
    printf("────────────────────────────"RST"\n");
}
*/