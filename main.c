/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:29:11 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/21 11:48:10 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"
#include <stdio.h>

t_brain	*new_brain(int width, int height, char *name)
{
	t_brain *new;
	t_point	size;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->color = 0x00FFFF;
	mlx_get_screen_size(new->ctx->mlx_ptr, &size.x, &size.y);
	if (width > size.x || height > size.y)
	{
		width = size.x;
		height = size.y;
		check_n_free(new->ctx->mlx_ptr);
		check_n_free(new->ctx);
		new->ctx = new_ctx(width, height);
	}
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->map = NULL;
	new->player = NULL;
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	init_keys(new);
	new->inited = 1;
	return (new);
}

int		loop_hook(t_brain *b)
{
	key_press(-1, b);
	if (b->player->as_move == 1)
	{
		draw_walls(b, b->ctx);
		update_sprite(b);
		if (is_key_pressed(b, 102) == -1)
			draw_minimap(b, 10, 25, 200);
		b->player->as_move = 0;
	}
	if (is_key_pressed(b, 102) != -1)
		draw_fullmap(b, 0.28);
	mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr,
													b->map->frame->img, 0, 0);
	fps_count(b->ctx);
	return (b->inited);
}

int		main(int ac, char **av)
{
	t_brain			*b;
	t_type			*map;
	

	if (ac != 2)
		return (-1);
	map = ft_getmap_flag(av[1]);
	printf("res 0 : %d res 1 : %d\n", map->res[0], map->res[1]);
	
	b = new_brain(map->res[0], map->res[1], "Cube3D");
	printf("ctx 0 : %d ctx 1 : %d\n", b->ctx->width, b->ctx->height);
	exit_cube(b, 0, "Init Exit", 1);
	
	printf("%d\n", map->height);
	ft_printf(GRN"Opening Map "DCYAN"%s\n"RST, av[1]);
	printf("ctx 0 : %d ctx 1 : %d\n", b->ctx->width, b->ctx->height);
	open_map(b, av[1], map);
	if (!check_map(b->map))
		exit_cube(b, 2, "BAD MAP", 0);

	ft_putstr(
		RED"\n🔥 L"YELO"O"GRN"O"CYAN"P "BLUE"I"PURP"N"PINK"I"RST"T 🔥\n\n"RST);
	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, 2, (1L<<0), &key_press, b);
	mlx_key_hook(b->ctx->win_ptr, &key_release, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
	ft_putstr("Loop Init OK\n");
	return (0);
}