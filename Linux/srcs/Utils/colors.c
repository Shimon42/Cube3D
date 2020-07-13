/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:47:34 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 14:58:17 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_rgb	hex_to_rgb(int color)
{
	t_rgb ret;

	ret.r = ((color >> 16) & 0xFF);
	ret.g = ((color >> 8) & 0xFF);
	ret.b = (color & 0xFF);
	return (ret);
}

int		rgb_to_hex(t_rgb color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

int		opacity(int color1, int color2, double opa)
{
	t_rgb	col1;
	t_rgb	col2;
	t_rgb	ret;

	col1 = hex_to_rgb(color1);
	col2 = hex_to_rgb(color2);
	ret.r = (int)floor(col1.r * opa) + (int)floor(col2.r * opa);
	ret.g = (int)floor(col1.g * opa) + (int)floor(col2.g * opa);
	ret.b = (int)floor(col1.b * opa) + (int)floor(col2.b * opa);
	return (rgb_to_hex(ret));
}

int		brightness(int color, double bright)
{
	int	ret;
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * bright;
	g = ((color >> 8) & 0xFF) * bright;
	b = (color & 0xFF) * bright;
	ret = (r << 16) + (g << 8) + b;
	return (ret);
}
