/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flags_disp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:57:07 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:28:46 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	disp_justif(int n, t_param *p, int left_justif)
{
	if (p)
		if (p->left_justif == left_justif && n > 0)
		{
			p->n_print += n;
			while (n-- > 0)
				ft_putchar(p->prefix);
		}
}

void	gest_wildcard(va_list va, t_param *p)
{
	if (p->min_field_as_var)
	{
		p->min_width = va_arg(va, int);
		if (p->min_width < 0)
		{
			p->left_justif = 1;
			p->prefix = ' ';
			p->min_width = ft_abs(p->min_width);
		}
	}
	if (p->max_field_as_var)
		p->precision = va_arg(va, int);
	if (!p->prefix)
		p->prefix = ' ';
}

void	print_zeros(t_param *p, int len)
{
	if (len > 0)
		while (len--)
		{
			p->n_print += write(1, "0", 1);
		}
}
