/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:52:35 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/17 10:46:13 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		disp_fps(t_ctx *c, char *str)
{
	if (str != NULL)
	{
		c->color = 0;
		c->text("FPS:", 10, 15, c);
		c->text(str, 35, 15, c);
	}
}

void		fps_count(t_ctx *c, int clear)
{
	static time_t	str_time = 0;
	static int		count = 0;
	static char		*str = NULL;

	if (clear == 1)
	{
		free(str);
		return ;
	}
	if (str_time == 0)
		str_time = time(0);
	if (time(0) - str_time >= 1)
	{
		str_time = time(0);
		c->fps = count;
		free(str);
		str = ft_itoa(count);
		count = 0;
	}
	else
		count++;
	disp_fps(c, str);
}
