/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 15:53:12 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 16:19:40 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/cube3d.h"

void	disp_point(t_point *p)
{
	printf("{ x:%6d, y:%6d }\n", p->x, p->y);
}

void	disp_map_s(t_map *m)
{
	printf("\nMap:\n\tHeight: [%d]\n\tWidth: [%d]\n\tBloc Size: [%d]\n\tScale: [%f]\n", m->width, m->height, m->bloc_size, m->scale);
}

void print_map_debug(char *line)
{
	while (*line)
	{
		if (*line == '0')
			ft_putstr(DGREY);
		else if (*line == '1')
			ft_putstr(DCYAN);
		else if (*line == '2')
			ft_putstr(YELO);
		else if (*line == 'N')
			ft_putstr(PINK); 
		ft_putchar(*line++);
	}
	ft_putchar('\n');
}

void		print_map_grid(t_map *map)
{
	int x;
	int y;
	int i;
	char val;

	i = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			val = map->grid[i];
			if (val == '0')
				ft_putstr(DGREY);
			else if (val == '1')
				ft_putstr(DCYAN);
			else if (val == '2')
				ft_putstr(YELO);
			else if (val == 'N')
				ft_putstr(PINK);
			else
				ft_putstr(RED);
			ft_putchar(val);
			if (x++ < map->width)
				ft_putchar(' ');
			i++;
		};
		ft_putchar('\n');
		y++;
	}
}

/*
void disp_brain(t_brain *b)
{
    t_param **params;

    params = &(b->params);
    printf(CYAN"┌────────────────────────────\n");
    printf("|----------- BRAIN ----------\n");
    printf("|\n");
    printf(YELO"|\tParams:\n");
    while (*params != NULL)
    {
		disp_param(*params);
        params = &((*params)->next);
    }
    printf("────────────────────────────"RST"\n");
}
*/