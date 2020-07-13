/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:50:12 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 18:26:21 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		ft_custom_strlen(const char *s, char c)
{
	int res;

	res = 0;
	while (s[res] && (s[res] != c))
		res++;
	return (res);
}

static	char	**ft_nb_part(char const *s, char c, int *len)
{
	int		nb_parts;
	int		i;
	char	**tab;

	i = 0;
	nb_parts = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
		{
			nb_parts++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
	}
	*len = nb_parts;
	if (((tab = malloc((nb_parts + 1) * sizeof(char *))) != NULL))
		tab[nb_parts] = NULL;
	else
		return (NULL);
	return (tab);
}

static void		ft_strcpy(char *dst, const char *src, int c)
{
	int i;

	i = 0;
	while (src[i] && (src[i] != c))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char		**ft_free_tab(char **tab, int len)
{
	while (len >= 0)
	{
		free(tab[len]);
		len--;
	}
	free(tab);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		len;
	int		curr;
	int		nb_parts;

	len = 0;
	i = 0;
	curr = 0;
	if (!s)
		return (NULL);
	tab = ft_nb_part(s, c, &nb_parts);
	while ((i < nb_parts) && tab)
	{
		while (s[curr] == c)
			curr++;
		len = ft_custom_strlen(&s[curr], c);
		if ((tab[i] = malloc(sizeof(char) * (len + 1))) != NULL)
			ft_strcpy(tab[i], &s[curr], c);
		else
			return (ft_free_tab(tab, i));
		i++;
		curr += len;
	}
	return (tab);
}
