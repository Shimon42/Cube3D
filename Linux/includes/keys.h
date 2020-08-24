/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:13:02 by user42            #+#    #+#             */
/*   Updated: 2020/08/24 12:41:23 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# define KEY_STYLE 1

# if KEY_STYLE == 0

/*
** -- AZERTY
*/

#  define UP_KEY 122
#  define DOWN_KEY 115
#  define LEFT_KEY 113
#  define RIGHT_KEY 100

# elif KEY_STYLE == 1

/*
** -- QWERTY
*/

#  define UP_KEY 119
#  define DOWN_KEY 115
#  define LEFT_KEY 97
#  define RIGHT_KEY 100

# endif

# define R_LEFT_KEY 65361
# define R_RIGHT_KEY 65363

# define JUMP_KEY 32

# define MAP_KEY 102

# define PAUSE_KEY 112

#endif
