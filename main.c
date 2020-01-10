/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/11 00:23:30 by siferrar    ###    #+. /#+    ###.fr     */
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


int		calc_dist(t_point p1, t_point p2)
{
	return ( sqrt( pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2)));
}

void	draw_line(t_ctx *ctx, t_point p1, t_point p2)
{
	double		diff_x;
	double		diff_y;
	double		pas_x;
	double		pas_y;
	double		dist;
	double		liss_x;
	double		liss_y;
	int			x;
	int			y;
	int i;

	i = 0;
	x = 0;
	y = 0;
	dist = calc_dist(p1, p2);
	diff_x = p2.x - p1.x;
	diff_y = p2.y - p1.y;
	pas_x = dist / diff_x;
	pas_y = dist / diff_y;
	printf("dist: %f\n", dist);
	printf("diff_x: %f\ndiff_y: %f\n", diff_x, diff_y);
	printf("pas_x: %f\npas_y: %f\n", pas_x, pas_y);

	while (p1.x + round(x) < p2.x && p1.y + round(y) < p2.y)
	{
		liss_x = 0;
		liss_y = 0;
		mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, p1.x + x, p1.y + y, ctx->color);
		if (round(pas_x) != 1)
		{
			while (liss_x < round(pas_x))
				mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, p1.x + x + liss_x++, p1.y + y, ctx->color);
			x += liss_x;
		}
		else 
			x += pas_x; 
		if (round(pas_y) != 1)
		{
			while (liss_y < round(pas_y))
				mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, p1.x +x, p1.y + y + liss_y++, ctx->color);
			y += liss_y;
		}
		else 
			y += pas_y;
		
		i++;
	}
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
	new->ctx = calloc(1, sizeof(t_ctx));
	new->ctx->mlx_ptr = mlx_init();
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0x00FFFF;
	return (new);
}

void meditate(t_brain *b)
{
	free(b->ctx->win_ptr);
	free(b->ctx->mlx_ptr);
	free(b->ctx);
	free(b);
}

int	main(void)
{
	t_brain *b;

	b = new_brain(1000, 1000, "Cube3D");
	draw_line(b->ctx, new_point(0,0), new_point(500,350));
	draw_line(b->ctx, new_point(0,0), new_point(400,10));

	mlx_key_hook(b->ctx->win_ptr, key_gest, 0);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}