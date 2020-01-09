/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 22:46:28 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"
#define PI 3.14159

int	key_gest(int keycode, void *param)
{
  param = 0;
  if (keycode == 65307)
    exit(1);
  return (0);
}

typedef struct	s_point
{
	int			x;
	int			y;

}				t_point;

typedef struct	s_ctx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			color;

}				t_ctx;

typedef struct	s_brain
{
	t_ctx		*ctx;
}				t_brain;


void	draw_line(t_ctx *ctx, t_point *p1, t_point *p2)
{
	int		diff_x;
	int		diff_y;
	int		i;

	i = 0;
	diff_x = abs(p2->x - p1->x);
	diff_y = abs(p2->y - p1->y);
	while (i > 300)
	{
		mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, p1->x + i, p1->y + i, ctx->color);
		i++;
	}
}

t_point	*new_point(int x, int y)
{
	t_point *new;

	new = calloc(1, sizeof(t_point));
	new->x = x;
	new->y = y;
	return (new);
}

t_brain *new_brain(int width, int height, char * name)
{
	t_brain *new;

	new = calloc(1, sizeof(new));
	new->ctx = calloc(1, sizeof(t_ctx));
	new->ctx->mlx_ptr = mlx_init();
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0xFF0000;
	return (new);
}

int	main(void)
{
	t_brain *b;

	b = new_brain(500, 500, "Cube3D");
	draw_line(b->ctx, new_point(0,0),new_point(100,100));

	mlx_key_hook(b->ctx->win_ptr, key_gest, 0);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}