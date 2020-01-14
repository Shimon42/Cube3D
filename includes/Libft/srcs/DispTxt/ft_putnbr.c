/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 21:17:49 by shimon       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 20:32:43 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_putnbr(long n)
{
	size_t count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n <= 9)
		count += ft_putchar(n + '0');
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	return (count);
}

void	ft_putnbr_fd(int n, int fd)
{
	long unb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		unb = (long)n * -1;
	}
	else
		unb = n;
	if (unb <= 9)
		ft_putchar_fd(unb + '0', fd);
	else
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putnbr_fd(unb % 10, fd);
	}
}
