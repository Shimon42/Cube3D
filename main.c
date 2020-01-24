/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:22:43 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"


int	key_press(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;
	printf(CYAN"Key [%d] pressed"RST"\n", key);
 	if (b && b->inited && b->player && b->player->inited)
	{
		if (key== 13)
			b->player->move(b->player, b->ctx);
		if (key == 0)
			b->player->angle -= b->player->rot_speed;
		if (key == 2)
			b->player->angle += b->player->rot_speed;
	}
	if (key == 53)
		exit(1);
	return (0);
}

int	key_release(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;
	printf(CYAN"Key [%d] released"RST"\n", key);
 	if (b && b->inited && b->player && b->player->inited)
	{
		if (key== 13)
			b->player->move(b->player, b->ctx);
		if (key == 0)
			b->player->angle -= b->player->rot_speed;
		if (key == 2)
			b->player->angle += b->player->rot_speed;
	}
	if (key == 53)
		exit(1);
	return (0);
}

t_point	new_point(int x, int y)
{
	t_point new;

	new.x = x;
	new.y = y;
	return (new);
}

t_brain *new_brain(int width, int height, char * name)
{
	t_brain *new;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0x00FFFF;
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
	
	draw_fullmap(b, (b->ctx->width / (b->map->width * b->map->bloc_size)));


	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, InputOnly, KeyRelease, &key_release, b);
	mlx_hook(b->ctx->win_ptr, InputOnly, KeyPress, &key_press, b);

	//mlx_key_hook(b->ctx->win_ptr, key_gest, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}