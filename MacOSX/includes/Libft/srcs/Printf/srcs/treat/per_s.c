/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:01:41 by siferrar          #+#    #+#             */
/*   Updated: 2020/04/29 15:29:27 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

void	disp_per_s(t_param *p, int len, char *str)
{
	int padding;
	int i;

	i = 0;
	padding = 0;
	p->n_print = 0;
	if (p->precision >= 0)
		if (p->precision < len)
			len = p->precision;
	if (p->min_width > len)
		padding += p->min_width - len;
	if (!p->pref_0)
		disp_justif(padding, p, 0);
	if ((p->pref_0 && !p->left_justif))
		while ((i < padding))
		{
			p->n_print += write(1, "0", 1);
			i++;
		}
	p->n_print += ft_putnstr(str, len);
	disp_justif(ft_abs(padding), p, 1);
}

int		per_s(va_list va, t_param *p)
{
	char	*str;
	int		len;
	int		wasnull;

	wasnull = 0;
	gest_wildcard(va, p);
	str = va_arg(va, char *);
	if (!str)
	{
		str = ft_strdup("(null)");
		wasnull = 1;
	}
	if (p->precision != 0)
		len = strlen(str);
	else
		len = 0;
	disp_per_s(p, len, str);
	if (wasnull)
		free(str);
	return (p->n_print);
}
