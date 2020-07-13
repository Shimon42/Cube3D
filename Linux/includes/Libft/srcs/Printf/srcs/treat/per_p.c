/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:01:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

size_t	ft_llhexlen(long long n)
{
	size_t length;

	length = 0;
	if (n == 0)
		length++;
	while (n != 0)
	{
		n /= 16;
		length++;
	}
	return (length);
}

int		per_p(va_list va, t_param *p)
{
	int				i;
	int				padding;
	unsigned long	nbr;

	i = 0;
	padding = 0;
	gest_wildcard(va, p);
	nbr = va_arg(va, unsigned long);
	if ((size_t)p->min_width > ft_llhexlen(nbr))
		padding += p->min_width - ft_llhexlen(nbr) - 2;
	padding -= p->is_sp_pref;
	if (!p->pref_0)
		disp_justif(padding, p, 0);
	p->n_print += write(1, "0x", 2);
	if ((p->pref_0 && !p->left_justif))
		while ((i < p->min_width - padding))
		{
			p->n_print += write(1, "0", 1);
			i++;
		}
	if (!(nbr == 0 && p->precision == 0))
		p->n_print += ft_puthex(nbr, 0);
	p->n_print += (p->show_sign);
	disp_justif(padding, p, 1);
	return (p->n_print);
}
