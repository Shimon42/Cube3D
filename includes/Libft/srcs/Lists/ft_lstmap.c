/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 16:59:39 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
