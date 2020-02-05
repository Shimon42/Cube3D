/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putint.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 22:21:52 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 00:37:52 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putint(char *name, int nbr)
{
	ft_putstr(name);
	ft_putchar(' ');
	ft_putnbr(nbr);
	ft_putchar('\n');
}
