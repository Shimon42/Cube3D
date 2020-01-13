/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 21:29:11 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 23:26:30 by siferrar    ###    #+. /#+    ###.fr     */
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
	new->ctx = calloc(1, sizeof(t_ctx));
	new->ctx->mlx_ptr = mlx_init();
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
/*
void	draw_line(t_ctx *ctx, t_point p1, t_point p2)
{
	//double		dist_a;
	double		rayon;
	//double		dist_c;
	double		cur_r;
	double		angle;
	int			x;
	int			y;
	int			prev_x;
	int			prev_y;
	int			i;
	t_point		p_a;
	t_point		vec1;
	t_point		vec2;
	double sinus;

	i = 0;
	x = 0;
	y = 0;
	rayon = calc_dist(p1, p2);
	p_a = new_point(p1.x, p1.y - rayon);
	vec1 = calc_diff(p_a, p1);
	vec2 = calc_diff(p1, p2);
	mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, p_a.x, p_a.y, ctx->color);
	disp_point(p1);
	disp_point(p2);
	//dist_a = calc_dist(p_a, p1);
	//dist_c = calc_dist(p2, p_a);
	//angle = ((- pow(dist_b,2)) + pow(dist_b, 2) + pow(dist_c, 2)) / (2 * dist_b * dist_c);
	angle = (calc_scal(vec1, vec2)) / (calc_norm(vec1) * calc_norm(vec2));
	disp_point(p_a);
	printf("rayon: %f\n", rayon);
	sinus = acosh(angle);
	sinus = sinus * (PI/180);
	printf("angle: %f\n", angle);
	cur_r = 0;
	while ((x != p2.x || y != p2.y) && i < 1000)
	{
		x = p1.x + (cur_r * cos(angle));
		y = p1.y + (cur_r * sin(angle));
		printf("{ x:%6d, y:%6d }\n", x, y);
		mlx_pixel_put (ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color);
		cur_r++;
		prev_x = x;
		prev_y = y;
		i++;
	}
	printf("i:%d\n", i);

}
*/
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
	draw_line(b->ctx, new_point(500,500), new_point(300,300));
	draw_line(b->ctx, new_point(500,500), new_point(500,300));
	draw_line(b->ctx, new_point(500,500), new_point(700,300));
	draw_line(b->ctx, new_point(500,500), new_point(700,500));
	draw_line(b->ctx, new_point(500,500), new_point(700,700));
	draw_line(b->ctx, new_point(500,500), new_point(500,700));
	draw_line(b->ctx, new_point(500,500), new_point(300,700));
	draw_line(b->ctx, new_point(500,500), new_point(300,500));

		draw_line(b->ctx, new_point(500,500), new_point(300,400));

	//mlx_pixel_put (b->ctx->mlx_ptr, b->ctx->win_ptr, 0, 0, b->ctx->color);
	mlx_key_hook(b->ctx->win_ptr, key_gest, 0);
	mlx_loop(b->ctx->mlx_ptr);
	return (0);
}