/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_findchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 16:46:48 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:10:52 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_findchar(const char *needles, const char *str)
{
	size_t i;
	size_t j;

	if (str && needles)
	{
		i = 0;
		while (str[i])
		{
			j = 0;
			while (needles[j] != '\0')
				if (needles[j++] == str[i])
					return (i);
			i++;
		}
	}
	return (-1);
}
