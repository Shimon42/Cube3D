/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meditate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 18:31:48 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/03 10:03:32 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	free_buff(t_buff *buff)
{
	ft_putstr("  -> Free buff\n");
	if (buff != NULL)
	{
		ft_putstr("     -> Free IMG - ");
		if (buff->img)
			free(buff->img);
		ft_putstr("OK\n");
		ft_putstr("     -> Free ADDR - ");
		/*if (buff->addr && buff->addr != NULL)
			free(buff->addr);*/
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

void	free_map(t_brain *b)
{
	int			i;
	t_sprite	*s;

	i = 0;
	ft_putstr(DYELO"Free Map\n");
	if (b != NULL && b->map != NULL)
	{
		free_buff(b->map->w_n);
		free_buff(b->map->w_e);
		free_buff(b->map->w_s);
		free_buff(b->map->w_w);
		free_buff(b->map->floor);
		free_buff(b->map->skybox);
		free_buff(b->map->frame);
		while (i < b->map->sprites->length)
			free(b->map->sprites->list[i++]);
		free(b->map->sprites->list);
		i = 0;
		while (i < b->map->height)
			free(b->map->grid[i++]); 
		check_n_free(b->map);
	}
}

void	meditate(t_brain *b)
{
	ft_putstr(DCYAN"Free Context\n");
	if (b->ctx != NULL)
	{
		free_buff(b->ctx->buff);
		check_n_free(b->ctx->win_ptr);
		check_n_free(b->ctx->mlx_ptr);
		check_n_free(b->ctx);
	}
	free_map(b);
	ft_putstr(DPINK"Free Player\n");
	if (b->player != NULL)
	{
		check_n_free(b->player->cam);
		check_n_free(b->player->pos);
		check_n_free(b->player->step);
		check_n_free(b->player);
	}
	ft_putstr(DGRN"Free Brain Struct\n");
	free(b);
}

void	exit_cube(t_brain *brain, int error_code, char *msg, int init)
{
	static t_brain *b = NULL;

	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("EXIT CUB INIT\n");
	}
	if (init)
		return ;
	if (error_code != 0)
		ft_putstr(RED);
	else
		ft_putstr(GRN);
	ft_putstr("\nCub3D Exit - Error: ");
	ft_putnbr(error_code);
	ft_putstr(" - ");
	ft_putstr(msg);
	ft_putstr("\n"RST);
	meditate(b);
	ft_putstr(GRN"Meditate OK\n");
	ft_putstr("Exit Done\n"RST);
	exit(0);
}
