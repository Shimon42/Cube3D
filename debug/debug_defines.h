/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siferrar <siferrar@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 07:12:16 by siferrar          #+#    #+#             */
/*   Updated: 2020/03/11 19:25:43 by siferrar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_DEFINES_H
# define DEBUG_DEFINES_H
# define DEBUG  0

/*
** -- Reset Colors
*/

# define RST "\033[0m"

/*
** -- Basic Colors
*/

# define RED    "\033[0;31m"
# define GRN    "\033[0;32m"
# define YELO   "\033[0;33m"
# define BLUE   "\033[0;34m"
# define PINK   "\033[0;35m"
# define CYAN   "\033[0;36m"
# define GREY   "\033[0;90m"
# define PURP   "\033[0;94m"

/*
** -- Bolded
*/

# define BRED	"\033[1;31m"
# define BGRN	"\033[1;32m"
# define BYELO	"\033[1;33m"
# define BBLUE  "\033[1;34m"
# define BPINK  "\033[1;35m"
# define BCYAN  "\033[1;36m"
# define BGREY  "\033[1;90m"
# define BPURP  "\033[1;94m"

/*
** -- Darker
*/

# define DRED	"\033[2;31m"
# define DGRN	"\033[2;32m"
# define DYELO	"\033[2;33m"
# define DBLUE 	"\033[2;34m"
# define DPINK	"\033[2;35m"
# define DCYAN	"\033[2;36m"
# define DGREY	"\033[2;90m"
# define DPURP	"\033[2;94m"

/*
** -- Italic
*/

# define IRED	"\033[3;31m"
# define IGRN	"\033[3;32m"
# define IYELO	"\033[3;33m"
# define IBLUE 	"\033[3;34m"
# define IPINK	"\033[3;35m"
# define ICYAN	"\033[3;36m"
# define IGREY	"\033[3;90m"
# define IPURP	"\033[3;94m"

/*
** -- Underlined
*/

# define UWHT   "\033[4;1m"
# define URED   "\033[4;31m"
# define UGRN   "\033[4;32m"
# define UYELO  "\033[4;33m"
# define UBLUE  "\033[4;34m"
# define UPINK  "\033[4;35m"
# define UCYAN  "\033[4;36m"
# define UGREY  "\033[4;90m"
# define UPURP  "\033[4;94m"

/*
** -- Highlighted
*/

# define HWHT   "\033[7;1m"
# define HRED   "\033[7;31m"
# define HGRN   "\033[7;32m"
# define HYELO  "\033[7;33m"
# define HBLUE  "\033[7;34m"
# define HPINK  "\033[7;35m"
# define HCYAN  "\033[7;36m"
# define HGREY  "\033[7;90m"
# define HPURP  "\033[7;94m"

/*
** -- Reverse Highlight
*/

# define RHWHT  "\033[7;1m"
# define RHRED  "\033[7;101m"
# define RHGRN  "\033[7;102m"
# define RHYELO "\033[7;103m"
# define RHBLUE "\033[7;104m"
# define RHPINK "\033[7;105m"
# define RHCYAN "\033[7;106m"
# define RHGREY "\033[7;100m"
# define RHPURP "\033[7;94m"

/*
** -- Misc
*/

# define BN    "\n"
# define TAB    "\t"
# define DTAB   "\t\t"
# define TTAB   "\t\t\t"
# define QTAB   "\t\t\t\t"
#endif
