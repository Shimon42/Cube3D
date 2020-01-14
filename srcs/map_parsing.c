/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parsing.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 20:36:43 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 23:02:28 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_putstr(char *str)
{
	size_t len;

	if (str)
	{
		len = ft_strlen(str);
		write(1, str, len);
	}
}

void print_map_debug(char *line)
{
	while (*line)
	{
		if (*line == '0')
			ft_putstr(DGREY);
		else if (*line == '1')
			ft_putstr(DCYAN);
		else if (*line == '2')
			ft_putstr(YELO); 
		ft_putchar(*line++);
	}
	ft_putchar('\n');
}

int				parse_map(t_brain *b, char *map_path)
{
	char	*line;
	int		file;
	int		ret;


	get_next_line(file, &line);
	file = open(map_path, O_RDONLY);
	while ((ret = get_next_line(file, &line)) != -1)
	{
		print_map_debug(line);
		if (!ret)
			break;
	}
	printf(GRN"MAP READ - OK"RST"\n");
	
	return (1);
}