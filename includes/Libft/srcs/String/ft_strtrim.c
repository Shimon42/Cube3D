/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 21:13:42 by shimon       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		n;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	n = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (s1[n])
		n++;
	n--;
	while ((n >= 0) && ft_strchr(set, s1[n]))
		n--;
	if (!(res = ft_substr(s1, 0, n + 1)))
		return (NULL);
	return (res);
}
