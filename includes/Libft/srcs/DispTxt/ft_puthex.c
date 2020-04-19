/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_puthex.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 20:42:44 by shimon       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 15:37:39 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_puthex(unsigned long n, int upper)
{
	size_t count;

	count = 0;
	if (n < 16)
	{
		if (upper)
			count += ft_putchar("0123456789ABCDEF"[n]);
		else
			count += ft_putchar("0123456789abcdef"[n]);
	}
	else
	{
		count += ft_puthex(n / 16, upper);
		count += ft_puthex(n % 16, upper);
	}
	return (count);
}
