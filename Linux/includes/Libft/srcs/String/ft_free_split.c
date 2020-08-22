/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:29:33 by siferrar          #+#    #+#             */
/*   Updated: 2020/07/22 20:33:22 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_split(char **splited)
{
	int i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
}
