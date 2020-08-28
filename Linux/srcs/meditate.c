/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meditate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 18:31:48 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/28 09:31:14 by user42           ###   ########lyon.fr   */
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

void	free_brain(t_brain *b)
{
	char *line;

	line = NULL;
	check_n_free(b->keys);
	check_n_free(b);
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
			free_buff(b, b->pause_menu);
			ft_putstr(DCYAN"Free Context\n");
			fps_count(b->ctx, 1);
			free_ctx(b->ctx);
		}
		ft_putstr(DGRN"Free Brain Struct\n");
		free_brain(b);
	}
}

void	exit_cube(t_brain *brain, int error_code, char *msg, int init)
{
	static t_brain *b = NULL;

	if (b == NULL && brain != NULL)
		b = brain;
	if (init)
		return ;
	ft_putstr(UCYAN"EXIT CUBE CALLED\n\n");
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
