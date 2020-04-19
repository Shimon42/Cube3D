/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:36:25 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_putnstr(char *str, size_t maxlen)
{
	size_t len;

	len = 0;
	if (str && maxlen > 0)
	{
		len = ft_strlen(str);
		if (maxlen && len > maxlen)
			len = maxlen;
		write(1, str, len);
	}
	return (len);
}
