/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:48:59 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:52:12 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list **tmp;

	tmp = NULL;
	if (*lst)
	{
		tmp = lst;
		while (*tmp)
		{
			*tmp = (*tmp)->next;
			ft_lstdelone(*tmp, del);
			*tmp = (*tmp)->next;
		}
		*tmp = NULL;
	}
	*lst = NULL;
}
