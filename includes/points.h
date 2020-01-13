/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   points.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 17:34:23 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 21:34:28 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef POINTS_H
# define POINTS_H

typedef struct	s_point
{
	int			x;
	int			y;

}				t_point;

void	disp_point(t_point p);
t_point	new_point(int x, int y);
#endif