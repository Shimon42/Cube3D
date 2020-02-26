/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:29:11 by siferrar          #+#    #+#             */
/*   Updated: 2020/02/26 08:08:17 by siferrar         ###   ########lyon.fr   */
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
	if (time(0) - str_time == 1)
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

int	is_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (i < 10 && key != -1)
	{
		if (b->keys[i] == key)
		{
			//printf("Key %d is pressed\n", key);
			//disp_keys(b);
			return (i);
		}
		i++;
	}
	return (-1);
}

int	add_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (b->keys[i] != -1 && i < 10)
		i++;
	if (i < 10)
	{
		b->keys[i] = key;
		//printf("Add %d\n", key);
		//disp_keys(b);
		return (1);
	}
	return (0);
}

int	del_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (b->keys[i] != key && i < 10)
		i++;
	if (i < 10 && b->keys[i] == key)
	{
		b->keys[i] = -1;
		return (1);
	}
	return (0);
}

int	key_press(int key, void *param)
{
	t_brain *b;	

	b = (t_brain*)param;
	if (key == 53)
		exit(1);
	if (key != -1 && is_key_pressed(b, key) == -1)
	{
		printf(CYAN"Key [%d] pressed"RST"\n", key);
		add_key_pressed(b, key);
	}
	if (b && b->inited && b->player && b->player->inited)
	{
		if ((key = is_key_pressed(b, 13)) >= 0)
			b->player->move(b->player, 1);
		if ((key = is_key_pressed(b, 1)) >= 0)
			b->player->move(b->player, -1);

		if ((key = is_key_pressed(b, 49)) >= 0)
			b->player->jump(b->player, 15);
		else if (b->player->z != 0)
		{
			b->player->jump(b->player, -10);
		}

		if ((key = is_key_pressed(b, 126)) >= 0 && b->player->cam->fov != ft_inrad(160))
		{
			b->player->as_move = 1;
			b->player->cam->fov = ft_inrad(170);
			b->player->cam->proj_size.x = 5000;
			b->player->cam->proj_size.y = 5000;
			b->player->cam->proj_dist = (b->player->cam->proj_size.x / 2) / tan(b->player->cam->fov / 2) * 2;
		}
	
		if ((key = is_key_pressed(b, 123)) >= 0 && is_key_pressed(b, 257) >= 0)
			b->player->rot(b->player, -b->player->rot_speed / 10);
		else if (key >= 0)
			b->player->rot(b->player, -b->player->rot_speed);
		if ((key = is_key_pressed(b, 124)) >= 0 && is_key_pressed(b, 257) >= 0)
			b->player->rot(b->player, b->player->rot_speed / 10);
		else if (key >= 0)
			b->player->rot(b->player, b->player->rot_speed);

		if ((key = is_key_pressed(b, 0)) >= 0)
			b->player->sidemove(b->player, -1);
		if ((key = is_key_pressed(b, 2)) >= 0)
			b->player->sidemove(b->player, 1);		
	}
	return (0);
}

int	key_release(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;

	if (key == 3)
	{
		draw_fullmap(b, 0);
		b->player->as_move = 1;
	}
	if (key == 49)
		b->player->jump(b->player, -5);
	
	if (key == 126)
	{
		b->map->bloc_size = 64;
		b->player->cam->fov = ft_inrad(60);
		b->player->cam->proj_size.x = b->ctx->width;
		b->player->cam->proj_size.y = b->ctx->height;
		b->player->cam->proj_dist = (b->player->cam->proj_size.x / 2) / tan(b->player->cam->fov / 2);
		b->player->as_move = 1;
	}
 	del_key_pressed(b, key);
	return (0);
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
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	new->keys = ft_calloc(10, sizeof(int));
	init_keys(new);
	new->inited = 1;
	return (new);
}

double		calc_dist(t_fpoint p1, t_fpoint p2)
{
	return ( sqrt( pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2)));
}

void meditate(t_brain *b)
{
	free(b->ctx->win_ptr);
	free(b->ctx->mlx_ptr);
	free(b->ctx);
	free(b);
}

int loop_hook(t_brain *b)
{
	key_press(-1, b);
	mlx_clear_window(b->ctx->mlx_ptr, b->ctx->win_ptr);

	//b->player->draw(b->player, b->ctx);
	if (b->player->as_move == 1)
	{
		draw_walls(b, b->ctx);
		if (is_key_pressed(b, 3) == -1)
			draw_minimap(b, 10, 25, 200);
		b->player->as_move = 0;
	} 
	if (is_key_pressed(b, 3) != -1)
	{
		draw_fullmap(b, 0.3);
	}
	mlx_put_image_to_window(b->ctx->mlx_ptr , b->ctx->win_ptr, b->map->frame->img, 0, 0);
	fps_count(b->ctx);
	//mlx_put_image_to_window(b->ctx->mlx_ptr , b->ctx->win_ptr, b->ctx->buff->img, 0, 0);
	//mlx_destroy_image(b->ctx->mlx_ptr, b->ctx->buff->img);
	return (b->inited);
}

int	main(int ac, char **av)
{
	t_brain *b;
	t_mlx_win_list *win;

	if(ac != 2)
		return (-1);
	b = new_brain(1920, 1080, "Cube3D");
	win = (t_mlx_win_list *)b->ctx->win_ptr;
	dprintf(1, "%d - %d\n", win->size_x, win->size_y);
	b->ctx->width = win->size_x;
	b->ctx->height = win->size_y;
	printf(GRN"Opening %s\n\n"RST, av[1]);
	open_map(b, av[1]);
	disp_point(b->player->pos);
	
	ft_putstr("Loop Init\n");
	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, InputOnly, KeyPress, &key_press, b);
	mlx_key_hook(b->ctx->win_ptr, &key_release, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
	ft_putstr("Loop Init OK\n");
	return (0);
}