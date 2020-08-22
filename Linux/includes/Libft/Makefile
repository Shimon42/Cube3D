NAME	= libft.a
INCPATH = includes/
SRCSPATH = srcs/

MEMLIB = $(SRCSPATH)Memory/
LISTSLIB = $(SRCSPATH)Lists/
MATHLIB = $(SRCSPATH)Math/
CONVLIB = $(SRCSPATH)Conv/
NUMLIB = $(SRCSPATH)Numbers/
STRLIB = $(SRCSPATH)String/
PRINTLIB = $(SRCSPATH)DispTxt/
FILESLIB = $(SRCSPATH)Files/
PRINTF = $(SRCSPATH)Printf/


SRCS	=	$(MATHLIB)ft_abs.c \
			\
			$(MEMLIB)ft_bzero.c \
			$(MEMLIB)ft_calloc.c \
			$(MEMLIB)ft_memccpy.c \
			$(MEMLIB)ft_memchr.c \
			$(MEMLIB)ft_memcmp.c \
			$(MEMLIB)ft_memcpy.c \
			$(MEMLIB)ft_memmove.c \
			$(MEMLIB)ft_memset.c \
			\
			$(PRINTLIB)ft_puthex.c \
			$(PRINTLIB)ft_putihex.c \
			$(PRINTLIB)ft_putchar.c \
			$(PRINTLIB)ft_putchar_fd.c \
			$(PRINTLIB)ft_putendl_fd.c \
			$(PRINTLIB)ft_putunbr.c \
			$(PRINTLIB)ft_putnbr.c \
			$(PRINTLIB)ft_putstr_fd.c \
			$(PRINTLIB)ft_putstr.c \
			$(PRINTLIB)ft_putnstr.c \
			$(PRINTLIB)ft_putint.c \
			\
			$(STRLIB)ft_split.c \
			$(STRLIB)ft_free_split.c \
			$(STRLIB)ft_strchr.c \
			$(STRLIB)ft_strdup.c \
			$(STRLIB)ft_strjoin.c \
			$(STRLIB)ft_strlcat.c \
			$(STRLIB)ft_strlcpy.c \
			$(STRLIB)ft_strlen.c \
			$(STRLIB)ft_strmapi.c \
			$(STRLIB)ft_strncmp.c \
			$(STRLIB)ft_strnstr.c \
			$(STRLIB)ft_findchar.c \
			$(STRLIB)ft_strrchr.c \
			$(STRLIB)ft_strtrim.c \
			$(STRLIB)ft_substr.c \
			$(STRLIB)ft_strupper.c \
			$(STRLIB)ft_toupper.c \
			$(STRLIB)ft_tolower.c \
			$(STRLIB)ft_isalnum.c \
			$(STRLIB)ft_isalpha.c \
			$(STRLIB)ft_isascii.c \
			$(STRLIB)ft_isdigit.c \
			$(STRLIB)ft_isprint.c \
			$(STRLIB)ft_check_str.c \
			\
			$(CONVLIB)ft_ftoa.c \
			$(CONVLIB)ft_atoi.c \
			$(CONVLIB)ft_itoa.c \
			$(CONVLIB)ft_itoab.c \
			$(CONVLIB)conv_angles.c \
			$(CONVLIB)ft_str_to_int_tab.c \
			\
			$(NUMLIB)ft_nbrslen.c \
			$(NUMLIB)ft_hexlen.c \
			\
			$(LISTSLIB)ft_lstnew.c \
			$(LISTSLIB)ft_lstadd_front.c \
			$(LISTSLIB)ft_lstlast.c \
			$(LISTSLIB)ft_lstsize.c \
			$(LISTSLIB)ft_lstadd_back.c \
			$(LISTSLIB)ft_lstiter.c \
			$(LISTSLIB)ft_lstdelone.c \
			$(LISTSLIB)ft_lstclear.c \
			$(LISTSLIB)ft_lstmap.c \
			\
			$(PRINTF)srcs/ft_printf.c \
			$(PRINTF)srcs/gest_params.c \
			$(PRINTF)srcs/gest_flags.c \
			$(PRINTF)srcs/gest_flags_disp.c \
			$(PRINTF)srcs/treat/per_per.c \
			$(PRINTF)srcs/treat/per_c.c \
			$(PRINTF)srcs/treat/per_s.c \
			$(PRINTF)srcs/treat/per_d.c \
			$(PRINTF)srcs/treat/per_u.c \
			$(PRINTF)srcs/treat/per_p.c \
			$(PRINTF)srcs/treat/per_x.c \
			$(PRINTF)srcs/treat/per_n.c

GNL = $(FILESLIB)GNL/
GNL_SRCS =	$(GNL)get_next_line.c \
			$(GNL)get_next_line_utils.c
GNL_OBJS	= ${GNL_SRCS:.c=.o}

GNL_BUFF_SIZE = 400

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g
CLEAR	= clear
RM		= rm -f
OBJS	= ${SRCS:.c=.o}

INCLUDES =	$(INCPATH)libft.h \
			$(GNL)get_next_line.h \
			$(PRINTF)includes/brain_printf.h \
			$(PRINTF)includes/printf.h

all:		$(NAME) $(OBJS) $(INCLUDES)

$(NAME): 	$(OBJS) $(INCLUDES)
			@echo "\033[0;32m––––––––––––––––––––––––\nMaking Libft\n––––––––––––––––––––––––\033[0;33m"
			clang -c $(CFLAGS) $(GNL_SRCS) -D BUFFER_SIZE=$(GNL_BUFF_SIZE)
			ar rc $(NAME) $(OBJS) get_next_line.o get_next_line_utils.o
			@echo "\033[0;m"

$(OBJS):	$(INCLUDES)

clean:		
			${RM} $(OBJS)
			${RM} get_next_line.o get_next_line_utils.o

fclean:		clean
			${RM} $(NAME)
			
re:			fclean all

.PHONY: all clean fclean re
