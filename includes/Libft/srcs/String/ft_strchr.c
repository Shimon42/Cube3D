/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 21:39:54 by shimon       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == c)
				return ((char*)&s[i]);
			i++;
		}
		if ((s[i] == c && c == '\0'))
			return ((char*)&s[i]);
	}
	return ((char *)NULL);
}
