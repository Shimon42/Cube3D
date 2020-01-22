/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 17:50:16 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"
#define PI 3.14159

int	key_gest(int keycode, void *param)
{
  param = 0;
  printf(CYAN"Key [%d] pressed"RST"\n", keycode);
  if (keycode == 53)
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

	new = calloc(1, sizeof(new));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	
	new->ctx->color = 0x00FFFF;
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

int	main(int ac, char **av)
{
	t_brain *b;

	if(ac != 2)
		return (-1);

	b = new_brain(1000, 1000, "Cube3D");
	draw_line(b->ctx, new_point(300,300), new_point(700,700));
	draw_line(b->ctx, new_point(300,500), new_point(700,500));
	draw_line(b->ctx, new_point(300,700), new_point(700,300));
	draw_line(b->ctx, new_point(500,300), new_point(500,700));

	
	open_map(b, av[1]);
	
	mlx_key_hook(b->ctx->win_ptr, key_gest, 0);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}