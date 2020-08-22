/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:49:16 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/17 11:36:09 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include "brain_printf.h"
# include "../../../includes/libft.h"

int			ft_printf(const char *str, ...) __attribute__((format(printf,1,2)));

t_param		*find_func(t_brain_prf *b, const char *str);
void		set_treat_func(t_brain_prf *b, t_param *cur, const char *str);
int			get_flags(t_param *ret, const char *str, int i);
int			get_min_width(t_param *ret, const char *str, int i);
int			get_precision(t_param *ret, const char *str, int i);
int			check_key(const char *str, char *tofind);

void		init_params_list(t_brain_prf **b);
t_param		*new_param(t_brain_prf *b);
void		add_param(t_brain_prf **b, char *key, void *f);
void		free_param(t_param *p);

void		disp_justif(int n, t_param *p, int left_justif);
void		gest_wildcard(va_list va, t_param *p);
void		print_zeros(t_param *p, int len);
int			check_flags(t_param *p);

int			per_per(va_list va, t_param *p);
int			per_c(va_list va, t_param *p);
int			per_s(va_list va, t_param *p);
int			per_d(va_list va, t_param *p);
int			per_p(va_list va, t_param *p);
int			per_u(va_list va, t_param *p);
int			per_x(va_list va, t_param *p);
int			per_n(va_list va, t_param *p);
int			per_f(va_list va, t_param *p);
#endif
