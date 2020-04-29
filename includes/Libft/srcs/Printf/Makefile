NAME	= libftprintf.a
INCPATH = includes/
SRCSPATH = srcs/
LIBFTPATH = $(SRCSPATH)Libft
FOLDNAME = Printf/

SRCS	=	$(SRCSPATH)$(FOLDNAME)ft_printf.c \
			$(SRCSPATH)$(FOLDNAME)gest_params.c \
			$(SRCSPATH)$(FOLDNAME)gest_flags.c \
			$(SRCSPATH)$(FOLDNAME)gest_flags_disp.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_per.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_c.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_s.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_d.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_u.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_p.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_x.c \
			$(SRCSPATH)$(FOLDNAME)treat/per_n.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
OBJS	= ${SRCS:.c=.o}

INCLUDES =	$(INCPATH)/brain.h \
			$(INCPATH)/printf.h

all:		$(NAME) $(OBJS) $(INCLUDES)

$(NAME): 	$(OBJS) $(INCLUDES)
			@echo "\033[0;32m––––––––––––––––––––––––\nCompiling Libft\n––––––––––––––––––––––––\033[0;33m"
			@$(MAKE) -C $(LIBFTPATH)
			@cp $(LIBFTPATH)/libft.a $(NAME)
			@echo "\033[0;32m––––––––––––––––––––––––\nPrintf Lib\n––––––––––––––––––––––––\033[0;33m"
			ar rcs $(NAME) $(OBJS)
			@echo "\033[0;m"

bonus:		all

comp: 		all
			$(CC) $(CFLAGS) main.c libftprintf.a

$(OBJS):	$(INCLUDES)

clean:		
			${RM} $(OBJS)
			$(MAKE) -C $(LIBFTPATH) clean

fclean:		clean
			${RM} $(NAME)
			$(MAKE) -C $(LIBFTPATH) fclean
			
re:			fclean all

.PHONY: all clean fclean re
