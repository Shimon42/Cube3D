/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbrslen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 18:36:40 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:11:30 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_ulen(unsigned int n)
{
	size_t length;

	length = 0;
	if (n == 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

int		ft_ilen(int n)
{
	int length;

	length = 0;
	if (n == 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

size_t	ft_llen(long n)
{
	size_t length;

	length = 0;
	if (n == 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}
