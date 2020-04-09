/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:29:11 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/04 12:34:10 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"
#include <time.h>

void		fps_count(t_ctx *c)
{
	static time_t str_time = 0;
	static int count = 0;
	static char *str = NULL;

	if (str_time == 0)
		str_time = time(0);
	if (time(0) - str_time >= 1)
	{
		str_time = time(0);
		free(str);
		str = ft_itoa(count);
		
		count = 0;
	} else
		count++;
	if (str != NULL)
	{
		c->color = 0;
		c->text("FPS:", 10, 2, c);
		c->text(str, 50, 2, c);
	}
}


t_fpoint	new_point(int x, int y)
{
	t_fpoint new;

	new.x = x;
	new.y = y;
	return (new);
}

void	init_keys(t_brain *b)
{
	int i;

	i = 0;
	while (i < 10)
		b->keys[i++] = -1;
}

t_brain *new_brain(int width, int height, char * name)
{
	t_brain *new;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0x00FFFF;
	new->map = NULL;
	new->player = NULL;
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	new->keys = ft_calloc(10, sizeof(int));
	init_keys(new);
	new->inited = 1;
	return (new);
}

float		calc_dist(t_fpoint p1, t_fpoint p2)
{
	return (sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y), 2)));
}

void exit_cube(t_brain *brain, int error_code, char *msg, int init)
{
	static t_brain *b = NULL;

	if (b == NULL && brain != NULL)
		b = brain;
	if (init)
		return ;
	if (error_code != 0)
		ft_putstr(RED);
	else
		ft_putstr(GRN);
	ft_putstr("\nCub3D Exit - Error: ");
	ft_putnbr(error_code);
	ft_putstr(" - ");
	ft_putstr(msg);
	ft_putstr("\n"RST);
	meditate(b);
	ft_putstr(GRN"Meditate OK\n");
	ft_putstr("Exit Done\n"GRN);
	exit (0);
}

void free_buff(t_buff *buff)
{
	ft_putstr("  -> Free buff - ");
	if (buff != NULL)
	{
		if (buff->img)
			free(buff->img);
		if (buff->addr)
			free(buff->addr);
	}
	free(buff);
	ft_putstr("OK\n");
}
void check_n_free(void *var)
{
	if (var != NULL)
		free(var);
}

void meditate(t_brain *b)
{
	/*
	** ----- FREE MAP
	*/

	ft_putstr(DYELO"Free Map\n");
	if (b->map != NULL)
	{
		free_buff(b->map->w_n);
		free_buff(b->map->w_e);
		free_buff(b->map->w_s);
		free_buff(b->map->w_w);
		free_buff(b->map->floor);
		free_buff(b->map->skybox);
		free_buff(b->map->frame);
		check_n_free(b->map);
	}

	/* 
	** ---- FREE CTX
	*/
	ft_putstr(DCYAN"Free Context\n");
	if (b->ctx != NULL)
	{
		free_buff(b->ctx->buff);
		check_n_free(b->ctx->win_ptr);
		check_n_free(b->ctx->mlx_ptr);
		check_n_free(b->ctx);
	}
	
	/* 
	** ---- FREE PLAYER
	*/
	ft_putstr(DPINK"Free Player\n");
	if (b->player != NULL)
	{
		check_n_free(b->player->cam);
		check_n_free(b->player->pos);
		check_n_free(b->player->step);
		check_n_free(b->player);
	}

	/*
	** ---- FREE BRAIN
	*/
	ft_putstr(DGRN"Free Brain Struct\n");
	free(b);
}

void	draw_sky(t_brain *b, t_ctx *c, double col, double end)
{
	int color;
	int y;
	static t_fpoint ratio = {-420, -420};
	static float width = 0;
	float left;

	if (ratio.x == -420)
	{
		ratio.y = (float)b->map->skybox->height / b->player->cam->proj_size.y;
		width = b->player->cam->proj_size.x * ((2 * PI) /  b->player->cam->fov);
		ratio.x = (float)b->map->skybox->width / width;
	}
	y = 0;
	left = -width * (b->player->angle / (2 * PI));
	if (left < width - b->player->cam->proj_size.x) 
		left += width;
	while (y < end)
	{
		color = pixel_get(b->map->skybox,
							col - left * ratio.x,
							200 - b->player->z*0.1 + y * ratio.y);
		pixel_put(col, y, color, b->map->frame);
		y++;
	}
}

int loop_hook(t_brain *b)
{
	mlx_clear_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
	key_press(-1, b);
	if (b->player->as_move == 1)
	{
		draw_walls(b, b->ctx);
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

int	check_map(t_map *m)
{
	t_point pos;
	int cur;
	int verif;

	pos.x = 0;
	while (pos.x < m->width)
	{
		pos.y = 0;
		while (pos.y < m->height)
		{
			cur = get_grid(m, pos.x, pos.y, 0);
			verif = get_grid(m, pos.x, pos.y - 1, 0);
			if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
				return (0);
			verif = get_grid(m, pos.x, pos.y + 1, 0);
			if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
				return (0);
			verif = get_grid(m, pos.x - 1, pos.y, 0);
			if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
				return (0);
			verif = get_grid(m, pos.x + 1, pos.y, 0);
			if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
				return (0);
			pos.y++;
		}
		pos.x++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_brain *b;
	t_mlx_win_list *win;

	if(ac != 2)
		return (-1);
	b = new_brain(1920, 1080, "Cube3D");
	exit_cube(b, 0, "Init Exit", 1);
	win = (t_mlx_win_list *)b->ctx->win_ptr;
	b->ctx->width = win->size_x;
	b->ctx->height = win->size_y;
	printf(GRN"Opening Map "DCYAN"%s\n"RST, av[1]);
	open_map(b, av[1]);
	if (!check_map(b->map))
		exit_cube(b, 2, "BAD MAP", 0);
	ft_putstr(RED"\n🔥 L"YELO"O"GRN"O"CYAN"P "BLUE"I"PURP"N"PINK"I"RST"T 🔥\n\n"RST);
	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, InputOnly, KeyPress, &key_press, b);
	mlx_key_hook(b->ctx->win_ptr, &key_release, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
	ft_putstr("Loop Init OK\n");
	return (0);
}