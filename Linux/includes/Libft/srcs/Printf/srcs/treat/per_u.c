/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:01:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

static void	gest_precision(t_param *p, int nbr, int len)
{
	int padding;

	padding = 0;
	if (p->min_width >= len && (p->precision != 0 || nbr == 0))
		padding += p->min_width;
	padding -= (p->is_sp_pref || p->show_sign);
	if (p->precision > len)
		padding -= p->precision;
	else if (p->precision > 0)
		padding -= len;
	else if (nbr != 0)
		padding += p->min_width - len;
	if (padding > 0)
		disp_justif(padding, p, 0);
	if ((!p->left_justif || p->precision) && (p->precision - len > 0))
		print_zeros(p, p->precision - len);
	if (p->precision || nbr != 0)
	{
		ft_putunbr(nbr);
		p->n_print += len;
	}
	disp_justif(padding, p, 1);
}

static void	gest_no_precision(t_param *p, int nbr, int len)
{
	int padding;

	padding = 0;
	if (p->min_width > len)
		padding += p->min_width - len;
	if (!p->pref_0)
		disp_justif(padding, p, 0);
	if (!p->left_justif && p->pref_0)
		print_zeros(p, padding);
	ft_putunbr(nbr);
	p->n_print += len;
	disp_justif(padding, p, 1);
}

int			per_u(va_list va, t_param *p)
{
	unsigned int	nbr;

	p->n_print = 0;
	gest_wildcard(va, p);
	nbr = va_arg(va, unsigned int);
	if (p->precision >= 0)
		gest_precision(p, nbr, ft_ulen(nbr));
	else
		gest_no_precision(p, nbr, ft_ulen(nbr));
	return (p->n_print);
}
