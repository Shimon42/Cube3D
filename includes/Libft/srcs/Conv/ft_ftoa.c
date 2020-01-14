/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ftoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 19:26:58 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 19:59:46 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_ftoa(float n, int dec)
{
	int i;
	int neg;
	double temp;
	char *str;
	int strlen;

	strlen = ft_llen((double)n + dec + 2);

	str = ft_calloc(strlen, sizeof(char));
	printf("len: %d\n", strlen);
	i = 0;
	neg = 0;
	printf("\n%f\n", n);
	ft_putnbr((long)n);
	n = n - (long)n;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	ft_putchar('.');
	n *= 10;
	while (i < 10 && i < dec)
	{
		ft_putnbr(n);
		temp = n - (int)n;
		printf("\ntemp:%f\n", temp);
		n = (temp * 10);
		printf("n:%f\n", n);
		i++;
	}

	ft_putstr("\n-------------------------------------------\n");
	return (str);
}