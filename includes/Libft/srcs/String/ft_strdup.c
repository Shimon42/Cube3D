/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 12:32:31 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	length;
	size_t	i;

	i = 0;
	length = 0;
	while (s1 && s1[length] != '\0')
		length++;
	if ((dup = malloc((length + 1) * sizeof(char))) != NULL)
	{
		if (s1)
		{
			if (length == 0)
				length++;
			while (i < length && s1[i] != '\0' && s1)
			{
				dup[i] = s1[i];
				i++;
			}
		}
		dup[i] = '\0';
	}
	return (dup);
}
