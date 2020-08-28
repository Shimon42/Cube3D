/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:32:22 by milosandric       #+#    #+#             */
/*   Updated: 2020/08/28 10:04:50 by user42           ###   ########lyon.fr   */
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
	p->speed = b->map->bloc_size * 2.5;
	p->rot_speed = 1.5;
	p->step = malloc(sizeof(t_fpoint *));
	if (p->step == NULL)
		exit_cube(NULL, 102, "Failed to malloc player step", 0);
	p->brain = b;
	p->as_move = 0;
	p->as_rotate = 0;
	p->bobbing = 0;
	p->jumping = 0;
	p->inited = 1;
	return (1);
}

void	gest_error_player(t_brain *b, t_player_detect *p_obj)
{
	char *line;

	free(p_obj);
	get_next_line(b->cur_fd, &line, 1);
	free(line);
	exit_cube(b, 801, "Init Player - Player already initied", 0);
}

int		init_player(t_brain *b, t_player_detect *p_obj, int pos_x, char angle)
{
	ft_printf(DCYAN"	-> Init player\n");
	if (b->player != NULL)
		gest_error_player(b, p_obj);
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
	b->player->speed_ratio = 2;
	b->player->rot(b->player, 0);
	b->player->ctx = b->ctx;
	b->player->bob_height = 5.0;
	b->player->z = 0;
	b->ctx->col_step = b->player->cam->fov / b->ctx->width;
	ft_printf(GRN"Player init - "DGRN"OK\n"RST);
	return (1);
}
