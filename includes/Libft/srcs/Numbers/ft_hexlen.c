/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hexlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 13:08:54 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_hexlen(unsigned int n)
{
	size_t length;

	length = 0;
	if (n == 0)
		length++;
	while (n != 0)
	{
		n /= 16;
		length++;
	}
	return (length);
}
