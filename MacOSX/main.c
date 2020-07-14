/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:29:11 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/14 14:50:01 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

t_brain	*new_brain(int width, int height, char *name)
{
	t_brain *new;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0x00FFFF;
	new->map = NULL;
	new->player = NULL;
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	init_keys(new);
	new->inited = 1;
	return (new);
}

int		loop_hook(t_brain *b)
{
	mlx_clear_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
	key_press(-1, b);
	if (b->player->as_move == 1)
	{
		draw_walls(b, b->ctx);
		update_sprite(b);
		if (is_key_pressed(b, 3) == -1)
			draw_minimap(b, 10, 25, 200);
		b->player->as_move = 0;
	}
	if (is_key_pressed(b, 3) != -1)
		draw_fullmap(b, 0.28);
	mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr,
													b->map->frame->img, 0, 0);
	fps_count(b->ctx);
	return (b->inited);
}

int red_cross(void *brain)
{
	exit_cube(brain, 0, "Exit From Red Cross", 0);
	return (1);
}

void	init_loop(t_brain *b, int save)
{
	if (save)
	{
		loop_hook(b);
		ft_create_bmp(b->map->frame);
		exit_cube(b, 0, "Exit After Save", 0);
	}
	else
	{
		ft_putstr("Loop Init OK\n");
		mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
		mlx_hook(b->ctx->win_ptr, 2, (1L << 0), &key_press, b);
		mlx_hook(b->ctx->win_ptr, 17, (1L << 16), &red_cross, b);
		mlx_key_hook(b->ctx->win_ptr, &key_release, b);
		mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
		mlx_loop(b->ctx->mlx_ptr);
	}
}

int		main(int ac, char **av)
{
	t_brain			*b;
	t_mlx_win_list	*win;
	t_type			*map;
	int				save;

	if (ac < 2 || ac > 3)
		exit_cube(NULL, 1, "Wrong number of arguments\n\
	launch with ./Cub3D <map_file> [--save]\n", 0);
	save = (ac == 3 && ft_strnstr("--save", av[2], 6) ? 1 : 0);
	if ((map = ft_getmap_flag(av[1])) == NULL)
		exit_cube(NULL, 404, "Map Not Found", 0);
	b = new_brain(map->res[0], map->res[1], "Cube3D");
	exit_cube(b, 0, "Init Exit", 1);
	win = (t_mlx_win_list *)b->ctx->win_ptr;
	b->ctx->width = win->size_x;
	b->ctx->height = win->size_y;
	ft_printf(GRN"Opening Map "DCYAN"%s\n"RST, av[1]);
	open_map(b, av[1], map);
	if (!check_map(b->map))
		exit_cube(b, 2, "BAD MAP", 0);
	ft_putstr(
		RED"\n🔥 L"YELO"O"GRN"O"CYAN"P "BLUE"I"PURP"N"PINK"I"RST"T 🔥\n\n"RST);
	init_loop(b, save);
	return (0);
}
