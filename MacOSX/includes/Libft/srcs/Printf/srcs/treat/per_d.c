/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:07:03 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

void	gest_sign_pref(t_param *p, int nbr)
{
	if (p->show_sign || nbr < 0)
	{
		if (nbr >= 0)
			ft_putchar('+');
		else if (ft_abs(nbr) >= 0)
			ft_putchar('-');
		p->n_print++;
	}
	if (p->is_sp_pref && nbr >= 0 && !p->show_sign)
		p->n_print += write(1, " ", 1);
}

void	gest_precision(t_param *p, int nbr, int len)
{
	int	padding;
	int	i;

	i = 0;
	padding = 0;
	if (p->min_width >= len && (p->precision != 0 || nbr == 0))
		padding += p->min_width;
	padding -= (p->is_sp_pref || p->show_sign || nbr < 0);
	if (p->precision > len)
		padding -= p->precision;
	else if (p->precision > 0)
		padding -= len;
	else if (nbr != 0)
		padding += p->min_width - len;
	if (padding > 0)
		disp_justif(padding, p, 0);
	gest_sign_pref(p, nbr);
	if ((!p->left_justif || p->precision) && (p->precision - len > 0))
		print_zeros(p, p->precision - len);
	if (!(nbr == 0 && p->precision == 0))
		p->n_print += ft_putnbr(ft_abs(nbr));
	disp_justif(padding, p, 1);
}

void	gest_no_precision(t_param *p, int nbr, int len)
{
	int padding;
	int i;

	i = 0;
	padding = 0;
	if (p->min_width > len)
		padding += p->min_width - len;
	padding -= (p->is_sp_pref || p->show_sign || nbr < 0);
	if (!p->pref_0)
		disp_justif(padding, p, 0);
	gest_sign_pref(p, nbr);
	if (!p->left_justif && p->pref_0)
		print_zeros(p, padding);
	p->n_print += ft_putnbr(ft_abs(nbr));
	disp_justif(padding, p, 1);
}

int		per_d(va_list va, t_param *p)
{
	long			nbr;
	int				i;

	i = 0;
	p->n_print = 0;
	gest_wildcard(va, p);
	if (!ft_strncmp(p->key, "NA", 2))
		nbr = 0;
	else
		nbr = va_arg(va, int);
	if (p->precision >= 0)
		gest_precision(p, nbr, ft_ilen(nbr));
	else
		gest_no_precision(p, nbr, ft_ilen(nbr));
	return (p->n_print);
}
