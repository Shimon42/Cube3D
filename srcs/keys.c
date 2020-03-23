/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 06:48:57 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/23 10:06:49 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	is_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (i < 10 && key != -1)
	{
		if (b->keys[i] == key)
			return (i);
		i++;
	}
	return (-1);
}

int	add_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (b->keys[i] != -1 && i < 10)
		i++;
	if (i < 10)
	{
		b->keys[i] = key;
		return (1);
	}
	return (0);
}

int	del_key_pressed(t_brain *b, int key)
{
	int i;

	i = 0;
	while (b->keys[i] != key && i < 10)
		i++;
	if (i < 10 && b->keys[i] == key)
	{
		b->keys[i] = -1;
		return (1);
	}
	return (0);
}

int	key_press(int key, void *param)
{
	t_brain *b;	

	b = (t_brain*)param;
	if (key == 53)
		exit_cube(b, 0, "Exit from red cross", 0);
	if (key != -1 && is_key_pressed(b, key) == -1)
		add_key_pressed(b, key);
	if (b && b->inited && b->player && b->player->inited)
	{
		if ((key = is_key_pressed(b, 13)) >= 0)
			b->player->move(b->player, 1);
		else if ((key = is_key_pressed(b, 1)) >= 0)
			b->player->move(b->player, -1);

		if ((key = is_key_pressed(b, 49)) >= 0)
			b->player->jump(b->player, 15);
		else if (b->player->z != 0 && b->player->jumping != 0)
			b->player->jump(b->player, 15);
	
		if ((key = is_key_pressed(b, 123)) >= 0 && is_key_pressed(b, 257) >= 0)
			b->player->rot(b->player, -b->player->rot_speed / 20);
		else if (key >= 0)
			b->player->rot(b->player, -b->player->rot_speed);
		if ((key = is_key_pressed(b, 124)) >= 0 && is_key_pressed(b, 257) >= 0)
			b->player->rot(b->player, b->player->rot_speed / 20);
		else if (key >= 0)
			b->player->rot(b->player, b->player->rot_speed);

		if ((key = is_key_pressed(b, 0)) >= 0)
			b->player->sidemove(b->player, -1);
		if ((key = is_key_pressed(b, 2)) >= 0)
			b->player->sidemove(b->player, 1);		
	}
	return (0);
}

int	key_release(int key, void *param)
{
	t_brain *b;

	b = (t_brain*)param;
	if (key == 3)
	{
		draw_fullmap(b, 0);
		b->player->as_move = 1;
	}
	if (key == 49)
		b->player->jump(b->player, 15);
 	del_key_pressed(b, key);
	return (0);
}