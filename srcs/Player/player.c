/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:24:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/09 19:17:08 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cube3d.h"

int		init_cam(t_brain *b)
{
	t_camera *cam;

	b->player->cam = malloc(sizeof(t_camera));
	cam = b->player->cam;
	cam->fov = ft_inrad(60);
	cam->proj_size.x = b->ctx->width;
	cam->proj_size.y = b->ctx->height;
	cam->proj_dist = (cam->proj_size.x / 2) / tan(cam->fov / 2);
	return (1);
}

float get_player_angle(char dir)
{
	if (dir == 'N')
		return (2 * PI * 0.75);
	if (dir == 'E')
		return (0);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	ft_putstr(RED"WRONG DIR\n");
	return (0);
}

int		init_values(t_brain *b, t_player *p)
{
	p->move = &move;
	p->sidemove = &side_move;
	p->rot = &rotate;
	p->jump = &jump;
	p->speed = b->map->bloc_size * 0.12;
	p->rot_speed = (3 * PI) / 180;
	p->step = malloc(sizeof(t_fpoint *));
	p->rot(p, 0);
	p->brain = b;
	p->as_move = 1;
	p->as_rotate = 1;
	p->bobbing = 1;
	p->jumping = 0;
	p->inited = 1;
}

int		init_player(t_brain *b, int pos_x, char angle)
{
	printf(DCYAN"	-> Init player at ");
	if ((b->player = malloc(sizeof(t_player))) == NULL)
		exit_cube(NULL, 1, "Failed to malloc player", 0);
	if ((b->player->pos = malloc(sizeof(t_fpoint))) == NULL)
		exit_cube(NULL, 101, "Failed to malloc player pos", 0);
	b->player->pos->x = ((pos_x + 1) * b->map->bloc_size) -
														(b->map->bloc_size/2);
	b->player->pos->y = (b->map->height * b->map->bloc_size) -
														(b->map->bloc_size/2);
	init_values(b, b->player);
	b->player->angle = get_player_angle(angle);
	b->player->ctx = b->ctx;
	disp_point(b->player->pos);
	ft_putstr("	-> Init Cam - ");
	init_cam(b);
	ft_putstr(DGRN"OK\n");
	printf(GRN"Player init - "DGRN"OK\n"RST);
	return (1);
}

