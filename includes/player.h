/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 18:52:51 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 21:20:07 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"
# include "my_canvas.h"

typedef struct	s_camera
{
	double		fov;
	t_point		proj_size;
	double		proj_dist;
}				t_camera;

typedef struct	s_player
{
	int			inited;
	t_point		*pos;
	t_fpoint	*r_pos;
	t_camera	*cam;
    double      angle;
	t_point		*step;
    double      rot_speed;
    double      speed;
	t_ctx		*ctx;
	void		*brain;
	void		(*rot)(struct s_player *, double);
	void		(*move)(struct s_player *, int);
	void		(*sidemove)(struct s_player *, int);
	void		(*draw)(struct s_player *, t_ctx *);
}				t_player;
#endif