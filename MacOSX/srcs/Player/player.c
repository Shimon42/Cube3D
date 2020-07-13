/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:32:22 by milosandric       #+#    #+#             */
/*   Updated: 2020/07/13 14:58:50 by siferrar         ###   ########lyon.fr   */
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

float	get_player_angle(char dir)
{
	if (dir == 'N')
		return (2 * PI * 0.75);
	if (dir == 'E')
		return (0);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	ft_putstr(RED"Unknown direction for get_player_angle in player.c\n"RST);
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
	if (p->step == NULL)
		exit_cube(NULL, 102, "Failed to malloc player step", 0);
	p->brain = b;
	p->as_move = 1;
	p->as_rotate = 1;
	p->bobbing = 0;
	p->jumping = 0;
	p->inited = 1;
	return (1);
}

int		init_player(t_brain *b, int pos_x, char angle)
{
	ft_printf(DCYAN"	-> Init player at ");
	if ((b->player = malloc(sizeof(t_player))) == NULL)
		exit_cube(NULL, 1, "Failed to malloc player", 0);
	if ((b->player->pos = malloc(sizeof(t_fpoint))) == NULL)
		exit_cube(NULL, 101, "Failed to malloc player pos", 0);
	b->player->pos->x = ((pos_x + 1) * b->map->bloc_size) -
												(b->map->bloc_size / 2);
	b->player->pos->y = (b->map->height * b->map->bloc_size) -
												(b->map->bloc_size / 2);
	init_cam(b);
	init_values(b, b->player);
	b->player->angle = get_player_angle(angle);
	b->player->rot(b->player, 0);
	b->player->ctx = b->ctx;
	b->player->bob_height = 5.0;
	b->player->z = 0;
	b->ctx->col_step = b->player->cam->fov / b->ctx->width;
	disp_point(*b->player->pos);
	ft_putstr("	-> Init Cam - ");
	ft_putstr(DGRN"OK\n");
	ft_printf(GRN"Player init - "DGRN"OK\n"RST);
	return (1);
}
