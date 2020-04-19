/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strupper.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 16:01:17 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strupper(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strdup(str);
	while (ret[i])
	{
		ret[i] = ft_toupper(ret[i]);
		i++;
	}
	return (ret);
}
