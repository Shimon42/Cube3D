/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:52:35 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/04 14:32:43 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		fps_count(t_ctx *c)
{
	static time_t	str_time = 0;
	static int		count = 0;
	static char		*str = NULL;

	if (str_time == 0)
		str_time = time(0);
	if (time(0) - str_time >= 1)
	{
		str_time = time(0);
		free(str);
		c->fps = count;
		str = ft_itoa(count);
		count = 0;
	}
	else
		count++;
	if (str != NULL)
	{
		c->color = 0;
		c->text("FPS:", 10, 15, c);
		c->text(str, 35, 15, c);
	}
}
