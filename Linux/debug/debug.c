/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:53:12 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/17 11:34:47 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>

void	disp_point(t_fpoint p)
{
	ft_printf("{ x:%6f, y:%6f }\n", p.x, p.y);
}

void	disp_buff(t_buff *b)
{
	if (b->img)
		ft_printf("\nimg: set\n");
	else
		ft_printf(RED"\nNO IMG\n"RST);
	ft_printf("addr: [%s]\n", b->addr);
	ft_printf("bit/pixel: [%d]\n", b->bits_per_pixel);
	ft_printf("line_len: [%d]\n", b->line_length);
	ft_printf("endian: [%d]\n", b->endian);
}

void	print_player_debug(t_brain *b)
{
	b->ctx->color = 0x88000000;
	b->ctx->rect(new_point(10, 10), new_point(200, 100), 1, b->ctx);
	b->ctx->color = 0xFFFFFF;
	b->ctx->text("PosX: ", 12, 12, b->ctx);
	b->ctx->text(ft_itoa(b->player->pos->x), 65, 12, b->ctx);
}

void	disp_brain(t_brain *b)
{
	ft_printf(CYAN"┌────────────────────────────\n");
	ft_printf("|----------- BRAIN ----------\n");
	ft_printf("|\n");
	ft_printf("|\tINITED: %d\n", b->inited);
	ft_printf("────────────────────────────"RST"\n");
}
