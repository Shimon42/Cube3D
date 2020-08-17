/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:48:30 by mandric           #+#    #+#             */
/*   Updated: 2020/08/17 11:37:49 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	ft_set_bmpheader(char *res, int width, int height)
{
	int	filesize;

	filesize = 54 + 3 * width * height;
	res[0] = 'B';
	res[1] = 'M';
	res[10] = (unsigned char)54;
	res[14] = (unsigned char)40;
	res[18] = (unsigned char)width;
	res[19] = (unsigned char)(width >> 8);
	res[20] = (unsigned char)(width >> 16);
	res[21] = (unsigned char)(width >> 24);
	res[22] = (unsigned char)height;
	res[23] = (unsigned char)(height >> 8);
	res[24] = (unsigned char)(height >> 16);
	res[25] = (unsigned char)(height >> 24);
	res[26] = (unsigned char)(1);
	res[28] = (unsigned char)(32);
}

static void	ft_set_bmpdata(char *bmpdata, t_buff *frame)
{
	int	i;
	int	j;
	int k;
	int addr_index;

	k = 0;
	i = frame->height;
	while (--i)
	{
		j = -1;
		while (++j < frame->width)
		{
			addr_index = (i * frame->line_length + j * frame->offset);
			bmpdata[k * 4] = *(int *)(frame->addr + addr_index);
			bmpdata[k * 4 + 1] = (*(int *)(frame->addr + addr_index) >> 8);
			bmpdata[k * 4 + 2] = (*(int *)(frame->addr + addr_index) >> 16);
			bmpdata[k * 4 + 3] = (unsigned char)0xFF;
			k++;
		}
	}
}

int			ft_create_bmp(t_buff *frame)
{
	char	*bmp;
	int		fd;
	int		size;

	size = frame->width * frame->height;
	if (!(bmp = (char *)ft_calloc(54 + size * 4, sizeof(int))) ||
		(fd = open("output.bmp", O_RDWR | O_CREAT, 0666)) < 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	ft_set_bmpheader(bmp, frame->width, frame->height);
	ft_set_bmpdata(bmp + 54, frame);
	if (write(fd, bmp, 54 + size * 4) < 0)
	{
		close(fd);
		free(bmp);
		ft_putstr("error\n");
		return (0);
	}
	free(bmp);
	close(fd);
	return (1);
}
