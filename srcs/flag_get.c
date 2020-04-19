/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosandric <milosandric@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:39:19 by milosand          #+#    #+#             */
/*   Updated: 2020/04/12 21:26:08 by milosandric      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void    ft_getmap_flag(int fd, t_type *map)
{
int     ret;
char    *line;

map->res[0] = 0;
ft_init_t_type(map);
ret = get_next_line(fd, &line);
while (ret && ((ft_strmultichr(line, " 012SNEW")) != 1))
{
ft_getmap_values(line, map);
ret = get_next_line(fd, &line);
}
ft_check_struct(map);
}

void    ft_getmap_values(char *line, t_type *map)
{
int res;

if (!(res = ft_strncmp(line, "R ", 2)))
ft_flag_res(line + 2, map->res, map);
else if (!(ft_strncmp(line, "NO ", 3)))
ft_flag_str(line + 3, &map->no, map);
else if (!(ft_strncmp(line, "SO ", 3)))
ft_flag_str(line + 3, &map->so, map);
else if (!(ft_strncmp(line, "WE ", 3)))
ft_flag_str(line + 3, &map->we, map);
else if (!(ft_strncmp(line, "EA ", 3)))
ft_flag_str(line + 3, &map->ea, map);
else if (!(ft_strncmp(line, "S ", 2)))
ft_flag_str(line + 2, &map->s, map);
else if (!(ft_strncmp(line, "F ", 2)))
ft_flag_str(line + 2, &map->f, map);
else if (!(ft_strncmp(line, "C ", 2)))
ft_flag_str(line + 2, &map->c, map);
else if (line[0] != '\0')
exit_flag(501,"Unkown identifier(s) in setup file\n", map);
else{}
}

void    ft_flag_str(char *str, char **target, t_type *map)
{
int fd;

if (ft_ext_check(str, ".xpm"))
{
if (*target[0] != 0)
	exit_flag(502,"Several textures provided for one identifiers\n", map);
if ((fd = open(str, O_RDONLY)) == -1)
	exit_flag(503, "Invalid path for one of the textures\n", map);
*target = ft_strdup(str);
close(fd);
}
else
exit_flag(504,"Please provide a \'.xpm\' file.\n", map);
}

void    ft_flag_color(char *str, int *target, t_type *map)
{
int i;
char **splited;

i = 0;
if (ft_str_search(str, "0123456789,"))
exit_flag(505,"Illegal character in color declaration\n", map);
if (target[3] != 0)
exit_flag(506,"One of the colors is provided several time\n", map);
i = 0;
splited = ft_split(str, ',');
while (splited[i] != NULL)
i++;
if (i != 3)
exit_flag(507,"wtf is that color\n", map);
i = 0;
target[0] = ft_atoi(splited[0]);
target[1] = ft_atoi(splited[1]);
target[2] = ft_atoi(splited[2]);
while (i < 3)
{
if ((target[i] > 255) || (target[i] < 0))
exit_flag(508,"One of the colors is not formatted correctly\n", map);
i++;
}
target[3] = 1;
}

void    ft_flag_res(char *str, int *target, t_type *map)
{
int i;
char **splited;

i = 0;
if (ft_str_search(str, "0123456789 "))
exit_flag(509, "Illegal character in resolution\n", map);
if (target[2] != 0)
exit_flag(510,"Make up your mind about the resolution\n", map);
splited = ft_split(str, ' ');
while (splited[i] != NULL)
i++;
if (i != 2)
exit_flag(511, "Resolution not gud\n", map);
target[0] = ft_atoi(str);
str = ft_strchr(str, ' ');
target[1] = ft_atoi(str);
if (target[0] >= 2560)
target[0] = 2559;
if (target[1] >= 1440)
target[1] = 1439;
if (target[0] < 100)
target[0] = 100;
if (target[1] < 100)
target[1] = 100;
target[2] = 1;
}

char    *ft_str_search(char *str, char *chrs)
{
int i;
int flag;

i = 0;
flag = 0;
if (str == NULL)
return (NULL);
while (*str)
{
while (chrs[i])
{
if (*str == chrs[i])
	flag = 1;
i++;
}
if (flag == 0)
return (str);
flag = 0;
i = 0;
str++;
}
return (NULL);
}


void ft_check_struct(t_type *map)
{
if ((map->res[2] == 0) || ((map->f[3] == 0) || (map->c[3] == 0)))
exit_flag(512,"The setup file lacks one or more information\n", map);
if (map->no[0] == 0)
exit_flag(513,"North texture missing\n", map);
if (map->so[0] == 0)
exit_flag(514,"South texture missing\n", map);
if (map->ea[0] == 0)
exit_flag(515,"East texture missing\n", map);
if (map->we[0] == 0)
exit_flag(516,"West texture missing\n", map);
if (map->s[0] == 0)
exit_flag(517,"Sprite texture missing\n", map);
}

int		ft_strmultichr(char *str, char *chrlst)
{
int		i;
char	*ptr;
int		flaged;

i = 0;
ptr = NULL;
flaged = 1;
if ((ft_strlen(str) == 0) || ((str == NULL) && (chrlst == NULL)))
return 0;
while (str[i])
{
if (!(ptr = ft_strchr(chrlst, str[i])))
flaged = 0;
i++;
}
return (flaged);
}

int		ft_ext_check(char *str, char *end)
{
int len;
int count;

len = ft_strlen(str) - 1;
count = ft_strlen(end) - 1;
if (len == count)
return (0);
while ((str[len--] == end[count]) && ((count > 0) && (len > 0)))
count--;
if (count == 0)
return (1);
else
return (0);
}

void	ft_init_t_type(t_type *map)
{
map->no = ft_calloc(1, sizeof(char));
map->so = ft_calloc(1, sizeof(char));
map->we = ft_calloc(1, sizeof(char));
map->ea = ft_calloc(1, sizeof(char));
map->s = ft_calloc(1, sizeof(char));
map->c = ft_calloc(1, sizeof(char));
map->f = ft_calloc(1, sizeof(char));
map->height = 0;
map->width = 0;
map->valid = 1;
map->res[0] = 0;
map->res[1] = 0;
map->res[2] = 0;
}

void	exit_flag(int err_num, char *str, t_type *map)
{
	ft_putstr(RED"Cub3d Exit - Error: ");
	ft_putnbr(err_num);
	ft_putstr(" - ");
	ft_putstr(str);
	ft_putstr("\n");
	free(map);
	exit(0);
}