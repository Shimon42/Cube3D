/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:32:29 by simeon            #+#    #+#             */
/*   Updated: 2020/05/20 13:27:17 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	put_text(char *str, int x, int y, t_ctx *ctx)
{
	mlx_string_put(ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color, str);
}
