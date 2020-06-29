/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_per.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:01:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

static void	gest_no_precision(t_param *p)
{
	int padding;

	padding = 0;
	if (p->min_width > 1)
		padding += p->min_width - 1;
	if (!p->pref_0)
		disp_justif(padding, p, 0);
	if (!p->left_justif && p->pref_0)
		print_zeros(p, padding);
	p->n_print += write(1, "%", 1);
	disp_justif(padding, p, 1);
}

int			per_per(va_list va, t_param *p)
{
	p->n_print = 0;
	gest_wildcard(va, p);
	gest_no_precision(p);
	return (p->n_print);
}
