/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandric <mandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:59:39 by siferrar          #+#    #+#             */
/*   Updated: 2020/05/20 17:52:25 by mandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*next;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	if ((new = ft_lstnew(f(lst->content))))
	{
		tmp = new;
		lst = lst->next;
		while (lst)
		{
			if (!(next = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&new, del);
				return (new);
			}
			tmp->next = next;
			tmp = tmp->next;
			lst = lst->next;
		}
	}
	else
		ft_lstclear(&new, del);
	return (new);
}
