/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:01:30 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:39:03 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		init_params_list(t_brain_prf **b)
{
	add_param(b, "c", &per_c);
	add_param(b, "s", &per_s);
	add_param(b, "d", &per_d);
	add_param(b, "p", &per_p);
	add_param(b, "u", &per_u);
	add_param(b, "i", &per_d);
	add_param(b, "x", &per_x);
	add_param(b, "u", &per_u);
	add_param(b, "%", &per_per);
	add_param(b, "n", &per_n);
}

t_param		*new_param(t_brain_prf *b)
{
	t_param *new;

	if (!(new = malloc(sizeof(t_param))))
		return (NULL);
	new->key = NULL;
	new->treat = NULL;
	new->min_width = 0;
	new->show_sign = 0;
	new->is_sp_pref = 0;
	new->hashtag = 0;
	new->precision = -1;
	new->left_justif = 0;
	new->pref_0 = 0;
	new->prefix = ' ';
	new->max_width = -1;
	new->min_field_as_var = 0;
	new->max_field_as_var = 0;
	new->n_print = 0;
	new->next = NULL;
	new->parent = b;
	return (new);
}

void		add_param(t_brain_prf **b, char *key, void *f)
{
	t_param *new;

	new = new_param(*b);
	if (new != NULL)
	{
		new->key = ft_strdup(key);
		new->treat = f;
		new->next = (*b)->params;
		(*b)->params = new;
	}
}

int			check_key(const char *str, char *tofind)
{
	size_t	x;
	size_t	i;
	char	upper;
	size_t	to_f_len;

	to_f_len = ft_strlen(tofind);
	x = 0;
	i = 0;
	if (tofind[0] != '\0')
	{
		upper = ft_toupper(str[x]);
		while (str[x] && upper == ft_toupper(tofind[x]) && x < to_f_len)
		{
			if (tofind[x + 1] == '\0')
				return (0);
			else if (upper != ft_toupper(tofind[x]))
				break ;
			x++;
		}
	}
	return (-1);
}

void		free_param(t_param *p)
{
	free(p->key);
	free(p);
}
