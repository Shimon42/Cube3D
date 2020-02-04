/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_angles.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 21:28:19 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 21:30:38 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

double ft_inrad(double angle)
{
	return ((angle * PI)/ 180);
}

double ft_indeg(double angle)
{
	return (angle * 180.0 / PI);
}