/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 01:24:29 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:52:29 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *newlst;

	if ((newlst = malloc(sizeof(t_list))) != NULL)
	{
		newlst->content = content;
		newlst->next = NULL;
	}
	return (newlst);
}
