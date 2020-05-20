/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:35:13 by milosandric       #+#    #+#             */
/*   Updated: 2020/05/20 13:19:09 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		is_key_pressed(t_brain *b, int key)
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

int		add_key_pressed(t_brain *b, int key)
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

int		del_key_pressed(t_brain *b, int key)
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
