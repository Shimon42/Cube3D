/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:52:51 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/12 08:51:09 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"
# include "my_canvas.h"

typedef struct	s_camera
{
	float		fov;
	t_fpoint	proj_size;
	float		proj_dist;
}				t_camera;

typedef struct	s_player
{
	int			inited;
	int			as_move;
	int			as_rotate;
	t_fpoint	*pos;
	float		z;
	t_camera	*cam;
	float		angle;
	t_fpoint	*step;
	float		rot_speed;
	float		speed;
	int			bobbing;
	int			jumping;
	t_ctx		*ctx;
	void		*brain;
	void		(*rot)(struct s_player *, float);
	void		(*move)(struct s_player *, int);
	void		(*sidemove)(struct s_player *, int);
	void		(*jump)(struct s_player *, float);
	void		(*draw)(struct s_player *, t_ctx *);
}				t_player;

#endif
