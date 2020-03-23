/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:58:38 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/23 10:21:45 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/my_canvas.h"

void	draw_circle(float c_x, float c_y, int ray, int fill, t_ctx *ctx)
{
    int          x;
    int          y;
    int          d;
    
    while ((fill == 1 && ray > 0) || fill == 0)
    {
        x = 0;
        y = ray;
        d = ray - 1;
        while(y >= x)
        {
            pixel_put(c_x + x, c_y + y, ctx->color, ctx->cur_buff);
            pixel_put(c_x + y, c_y + x, ctx->color, ctx->cur_buff);
            pixel_put(c_x - x, c_y + y, ctx->color, ctx->cur_buff);
            pixel_put(c_x - y, c_y + x, ctx->color, ctx->cur_buff);
            pixel_put(c_x + x, c_y - y, ctx->color, ctx->cur_buff);
            pixel_put(c_x + y, c_y - x, ctx->color, ctx->cur_buff);
            pixel_put(c_x - x, c_y - y, ctx->color, ctx->cur_buff);
            pixel_put(c_x - y, c_y - x, ctx->color, ctx->cur_buff);
            
            if (d >= 2 * x)
            {
                d -= 2 * x + 1;
                x++;
            }
            else if (d < 2 * (ray - y))
            {
                d += 2 * y - 1;
                y--;
            }
            else
            {
                d += 2 * (y - x - 1);
                y--;
                x++;
            }
        }
        if (!fill)
            return ;
        ray--;
    }
    pixel_put(c_x, c_y, ctx->color, ctx->cur_buff);
}