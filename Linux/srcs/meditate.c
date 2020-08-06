/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meditate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 18:31:48 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/06 12:06:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	free_buff(t_brain *b, t_buff *buff)
{
	ft_putstr("  -> Free buff\n");
	if (buff != NULL)
	{
		ft_putstr("     -> Free IMG - ");
		if (buff->img != NULL)
			mlx_destroy_image(b->ctx->mlx_ptr, buff->img);
		ft_putstr("OK\n");
		ft_putstr("     -> Free ADDR - ");
		ft_putstr("OK\n");
		free(buff);
	}
	ft_putstr("OK\n");
}

void	check_n_free(void *var)
{
	if (var != NULL)
		free(var);
}

void	meditate(t_brain *b)
{
	if (b)
	{
		free_map(b);
		ft_putstr(DPINK"Free Player\n");
		if (b->player != NULL)
		{
			check_n_free(b->player->cam);
			check_n_free(b->player->pos);
			check_n_free(b->player->step);
			check_n_free(b->player);
		}
		if (b->ctx != NULL)
		{
			ft_putstr(DCYAN"Free Context\n");
			free_buff(b, b->ctx->buff);
			if (!b->save && b->ctx->win_ptr)
				mlx_destroy_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
			check_n_free(b->ctx);
			free(b->ctx->mlx_ptr);
		}
		ft_putstr(DGRN"Free Brain Struct\n");
		free(b->keys);
		free(b);
	}
}

void	exit_cube(t_brain *brain, int error_code, char *msg, int init)
{
	static t_brain *b = NULL;

	ft_putstr(UCYAN"EXIT CUBE CALLED\n\n");
	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("EXIT CUB INIT\n");
	}
	if (init)
		return ;
	meditate(b);
	ft_putstr(GRN"Meditate OK\n");
	if (error_code != 0)
		ft_putstr(RED);
	else
		ft_putstr(GRN);
	ft_putstr("\nCub3D Exit Done - Error: ");
	ft_putnbr(error_code);
	ft_putstr(" - ");
	ft_putstr(msg);
	ft_putstr("\n"RST);
	exit(0);
}
