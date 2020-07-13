/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:49:21 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:39:03 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

t_param		*find_func(t_brain_prf *b, const char *str)
{
	t_param **tmp;
	t_param **ret;
	int		first_found;
	int		found;

	tmp = &(b->params);
	ret = NULL;
	first_found = ft_strlen(str);
	while (*tmp != NULL)
	{
		if ((found = check_key(str, (*tmp)->key)) > -1)
		{
			ret = tmp;
			(*ret)->key[0] = str[found];
			break ;
		}
		tmp = &((*tmp)->next);
	}
	if (ret == NULL)
		return (NULL);
	return (*ret);
}

void		set_treat_func(t_brain_prf *b, t_param *cur, const char *str)
{
	t_param *res;

	res = find_func(b, str);
	if (res)
	{
		cur->treat = res->treat;
		cur->key = ft_strdup(res->key);
	}
	else
	{
		ft_putstr("TREAT FUNC NOT FOUND\n");
		res = find_func(b, "d");
		cur->treat = res->treat;
		cur->key = ft_strdup("NA");
	}
}

int			get_flags(t_param *ret, const char *str, int i)
{
	while (ft_strchr("-+0 #", str[i]))
	{
		if (str[i] == '-')
		{
			ret->left_justif = 1;
			ret->prefix = ' ';
		}
		else if (str[i] == '+')
			ret->show_sign = 1;
		else if (str[i] == ' ')
			ret->is_sp_pref = 1;
		else if (str[i] == '0' && !ret->left_justif)
		{
			ret->prefix = '0';
			ret->pref_0 = 1;
		}
		else if (str[i] == '#')
			ret->hashtag = 1;
		i++;
	}
	return (i);
}

int			get_min_width(t_param *ret, const char *str, int i)
{
	if (str[i] == '*')
	{
		ret->min_field_as_var = 1;
		i++;
	}
	else if (str[i] >= '1' && str[i] <= '9' && !ret->min_field_as_var)
	{
		ret->min_width = ft_atoi(str + i);
		if (!ret->prefix)
			ret->prefix = ' ';
		i += ft_ilen(ret->min_width);
	}
	return (i);
}

int			get_precision(t_param *ret, const char *str, int i)
{
	if (str[i] == '.')
	{
		i++;
		ret->prefix = ' ';
		if (str[i] >= '0' && str[i] <= '9')
		{
			while (str[i] == '0')
				i++;
			ret->precision = ft_atoi(str + i);
			if (ret->precision)
				i += ft_ilen(ret->precision);
		}
		else if (str[i] == '*')
		{
			ret->max_field_as_var = 1;
			i++;
		}
		else
			ret->precision = 0;
	}
	return (i);
}
