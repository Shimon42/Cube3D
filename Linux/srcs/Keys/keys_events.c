/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 06:48:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/07 15:11:33 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	action_keys(int key, t_brain *b)
{
	if (b && b->inited && b->player && b->player->inited)
	{
		if ((key = is_key_pressed(b, UP_KEY)) >= 0)
			b->player->move(b->player, 1);
		else if ((key = is_key_pressed(b, DOWN_KEY)) >= 0)
			b->player->move(b->player, -1);
		if ((key = is_key_pressed(b, JUMP_KEY)) >= 0)
			b->player->jump(b->player, 3.5);
		else if (b->player->z != 0 && b->player->jumping != 0)
			b->player->jump(b->player, 3.5);
		if ((key = is_key_pressed(b, R_LEFT_KEY)) >= 0
			&& is_key_pressed(b, 65505) >= 0)
			b->player->rot(b->player, -b->player->rot_speed / 20);
		else if (key >= 0)
			b->player->rot(b->player, -b->player->rot_speed);
		if ((key = is_key_pressed(b, R_RIGHT_KEY)) >= 0
			&& is_key_pressed(b, 65505) >= 0)
			b->player->rot(b->player, b->player->rot_speed / 20);
		else if (key >= 0)
			b->player->rot(b->player, b->player->rot_speed);
		if ((key = is_key_pressed(b, LEFT_KEY)) >= 0)
			b->player->sidemove(b->player, -1);
		if ((key = is_key_pressed(b, RIGHT_KEY)) >= 0)
			b->player->sidemove(b->player, 1);
	}
}

void	calc_speed_ratio(t_brain *b)
{
	static clock_t	old_time = 0;
	float			diff;

	if (old_time == 0)
		old_time = clock();
	diff = ((clock() - old_time) / 1000000.0);
	b->player->speed_ratio = diff;
	old_time = clock();
}

int		key_press(int key, void *param)
{
	t_brain	*b;

	b = (t_brain*)param;
	if (key == 65307)
		exit_cube(b, 0, "Exit from Escape key", 0);
	if (key != -1 && is_key_pressed(b, key) == -1)
		add_key_pressed(b, key);
	calc_speed_ratio(b);
	action_keys(key, b);
	return (0);
}

int		key_release(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;
	if (key == 49)
		b->player->jump(b->player, 15);
	del_key_pressed(b, key);
	return (0);
}
