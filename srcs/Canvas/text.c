/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:32:29 by simeon            #+#    #+#             */
/*   Updated: 2020/05/08 17:31:36 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_canvas.h"

void	put_text(char *str, int x, int y, t_ctx *ctx)
{
	mlx_string_put(ctx->mlx_ptr, ctx->win_ptr, x, y, ctx->color, str);
}
