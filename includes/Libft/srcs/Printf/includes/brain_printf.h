/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:15:38 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:54:42 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_PRINTF_H
# define BRAIN_PRINTF_H

typedef struct			s_param
{
	char				*key;
	int					(*treat)(void *, void *);
	int					left_justif;
	int					min_field_as_var;
	int					max_field_as_var;
	int					min_width;
	int					max_width;
	int					show_sign;
	int					is_sp_pref;
	char				prefix;
	int					pref_0;
	int					hashtag;
	int					precision;
	int					flags_length;
	int					n_print;
	int					upper;
	struct s_param		*next;
	struct s_brain_prf	*parent;
}						t_param;

typedef	struct			s_brain_prf
{
	t_param				*params;
	t_param				*cur_param;
	int					n_print;
	long				stri;
}						t_brain_prf;

#endif
