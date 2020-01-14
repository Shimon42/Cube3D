NAME =		Cube3D

SRCSPATH =	srcs/
INCPATH =	includes/

MINILIB =	$(INCPATH)MiniLib/

INCLUDES =	$(INCPATH)cube3d.h \
			$(INCPATH)points.h \
			$(INCPATH)Gnl/get_next_line.h \
			\
			$(MINILIB)mlx.h \
			\
			debug.h


SRCS = 		main.c \
			$(INCPATH)Gnl/get_next_line.c \
			$(INCPATH)Gnl/get_next_line_utils.c \
			$(SRCSPATH)draw_line.c \
			$(SRCSPATH)Drawing/rect.c \
			debug.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
GNLBUFF =	-D BUFFER_SIZE=100

OBJS = ${SRCS:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			@make -C $(MINILIB)
			ar rc $(NAME).a $(OBJS)

comp:		all
			@gcc $(CFLAGS) main.c -D BUFFER_SIZE=100 $(NAME).a -o $(NAME) -framework OpenGL -framework AppKit

launch:		comp
			./Cube3D

minilib:	
			@make -C $(MINILIB)

$(OBJS):	$(INCLUDES)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all