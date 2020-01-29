/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simeon <simeon@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 15:24:38 by simeon      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"

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
		//printf("Key %d deleted\n", key);
		//disp_keys(b);
		return (1);
	}
	return (0);
}

int	key_press(int key, void *param)
{
	t_brain *b;	

	b = (t_brain*)param;
	if (key != -1 && is_key_pressed(b, key) == -1)
	{
		printf(CYAN"Key [%d] pressed"RST"\n", key);
		add_key_pressed(b, key);
	}
	if (b && b->inited && b->player && b->player->inited)
	{
		if (is_key_pressed(b, 13) >= 0)
			b->player->move(b->player, 1);
		if (is_key_pressed(b, 1) >= 0)
			b->player->move(b->player, -1);
		if (is_key_pressed(b, 0) >= 0)
			b->player->rot(b->player, -1);
		if (is_key_pressed(b, 2) >= 0)
			b->player->rot(b->player, 1);
	}
	if (key == 53)
		exit(1);
	return (0);
}

int	key_release(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;
//	printf(CYAN"Key [%d] released"RST"\n", key);
 	del_key_pressed(b, key);
	return (0);
}

t_point	new_point(int x, int y)
{
	t_point new;

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
	new->keys = ft_calloc(10, sizeof(int));
	init_keys(new);
	new->inited = 1;
	return (new);
}

int		calc_dist(t_point p1, t_point p2)
{
	return ( sqrt( pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2)));
}

double	calc_norm(t_point p)
{
	return(sqrt(pow(p.x, 2) + pow(p.y, 2)));
}

int		calc_scal(t_point p1, t_point p2)
{
	return (p1.x * p2.x) + (p1.y * p2.y);
}

t_point	calc_diff(t_point p1, t_point p2)
{
	t_point ret;

	ret.x = p1.x - p2.x;
	ret.y = p1.y - p2.y;
	return (ret);
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
	init_buff(b->ctx);
//	b->player->draw(b->player, b->ctx);
	//draw_minimap(b, 10, 10, 1);
	draw_fullmap(b, (b->ctx->width / (b->map->width * b->map->bloc_size)));
	print_player_debug(b);
	mlx_put_image_to_window(b->ctx->mlx_ptr , b->ctx->win_ptr, b->ctx->buff->img, 0, 0);
	mlx_destroy_image(b->ctx->mlx_ptr, b->ctx->buff->img);
	return (b->inited);
}

int	main(int ac, char **av)
{
	t_brain *b;

	if(ac != 2)
		return (-1);
	b = new_brain(1000, 1000, "Cube3D");
	printf(GRN"Opening %s\n\n"RST, av[1]);
	open_map(b, av[1]);
	
	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, InputOnly, KeyPress, &key_press, b);
	mlx_key_hook(b->ctx->win_ptr, &key_release, b);

	//mlx_key_hook(b->ctx->win_ptr, key_gest, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}