/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 10:41:58 by user42            #+#    #+#             */
/*   Updated: 2020/08/18 19:17:32 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

t_brain	*new_brain(int width, int height, int save)
{
	t_brain *new;
	t_point	size;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->save = save;
	mlx_get_screen_size(new->ctx->mlx_ptr, &size.x, &size.y);
	if (width > size.x || height > size.y)
	{
		if (width > size.x)
			width = size.x;
		if (height > size.y)
			height = size.y;
		check_n_free(new->ctx->mlx_ptr);
		check_n_free(new->ctx);
		new->ctx = new_ctx(width, height);
		new->ctx->fps = 0;
	}
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
	draw_walls(b, b->ctx);
	update_sprite(b);
	if (is_key_pressed(b, MAP_KEY) == -1)
	{
		draw_minimap(b, 10, 25, 200);
		draw_fullmap(b, 0);
	}
	else
		draw_fullmap(b, 0.28);
	if (!b->save)
		mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr,
													b->map->frame->img, 0, 0);
	fps_count(b->ctx, 0);
	return (b->inited);
}

int		red_cross(void *brain)
{
	t_brain	*b;

	b = (t_brain*)brain;
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
		b->ctx->win_ptr = mlx_new_window(b->ctx->mlx_ptr,
			b->ctx->width, b->ctx->height, "Cube3D");
		mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
		mlx_hook(b->ctx->win_ptr, 2, (1L << 0), &key_press, b);
		mlx_hook(b->ctx->win_ptr, 33, (1L << 17), &red_cross, b);
		mlx_hook(b->ctx->win_ptr, 3, (1L << 1), &key_release, b);
		mlx_do_sync(b->ctx->mlx_ptr);
		mlx_loop(b->ctx->mlx_ptr);
	}
}

int		main(int ac, char **av)
{
	t_brain			*b;
	t_type			*map;
	int				save;

	save = 0;
	if (ac == 3 && ft_strnstr("--save", av[2], 6))
		save = 1;
	else if ((ac != 2) && (save == 0))
		exit_cube(NULL, 1, "Wrong argument\n\
	launch with ./Cub3D <map_file> [--save]\n", 0);
	if ((map = ft_getmap_flag(av[1])) == NULL)
		exit_cube(NULL, 404, "Map Not Found", 0);
	b = new_brain(map->res[0], map->res[1], save);
	exit_cube(b, 0, "Init Exit", 1);
	ft_printf(GRN"Opening Map "DCYAN"%s\n"RST, av[1]);
	open_map(b, av[1], map);
	if (!check_map(b->map))
		exit_cube(b, 2, "BAD MAP", 0);
	ft_putstr(
		RED"\n🔥 L"YELO"O"GRN"O"CYAN"P "BLUE"I"PURP"N"PINK"I"RST"T 🔥\n\n"RST);
	init_loop(b, save);
	return (0);
}
