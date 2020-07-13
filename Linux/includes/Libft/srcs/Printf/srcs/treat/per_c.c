/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:01:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

int	per_c(va_list va, t_param *p)
{
	int				i;
	int				padding;

	i = 0;
	gest_wildcard(va, p);
	p->n_print = 1;
	padding = 1 + p->is_sp_pref;
	if (!p->pref_0)
		disp_justif(p->min_width - padding, p, 0);
	if ((p->pref_0 && !p->left_justif))
		while ((i < p->min_width - padding))
		{
			p->n_print += write(1, "0", 1);
			i++;
		}
	ft_putchar(va_arg(va, int));
	disp_justif(p->min_width - padding, p, 1);
	return (p->n_print);
}
