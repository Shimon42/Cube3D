NAME =		Cube3D

SRCSPATH =	srcs/
INCPATH =	includes/

#---------  LIBS --
MINILIB =	$(INCPATH)MiniLib/
LIBFT =		$(INCPATH)Libft/

#---------	INCLUDES --
INCLUDES =	$(INCPATH)cube3d.h \
			$(INCPATH)brain.h \
			$(INCPATH)my_canvas.h \
			$(INCPATH)map.h \
			$(INCPATH)Gnl/get_next_line.h \
			$(LIBFT)includes/libft.h \
			\
			$(MINILIB)mlx.h \
			\
			debug.h

#--------	SRCS --
SRCS = 		main.c \
			$(SRCSPATH)Canvas/draw_line.c \
			$(SRCSPATH)Canvas/rect.c \
			$(SRCSPATH)Canvas/context.c \
			$(SRCSPATH)map_parsing.c \
			$(SRCSPATH)draw_map.c \
			debug.c

GNL_SRCS =	$(INCPATH)Gnl/get_next_line.c \
			$(INCPATH)Gnl/get_next_line_utils.c

GNL_OBJS =	${GNL_SRCS:.c=.o}

CC =		gcc

CFLAGS	= -Wall -Wextra -Werror
CFLAGSs	= 

OBJS = ${SRCS:.c=.o}

MAPS	= assets/
MAP1 = $(MAPS)map.cub

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			make -C $(MINILIB)
			make -C $(LIBFT)
			gcc -c $(GNL_SRCS) -D BUFFER_SIZE=128
			cp $(MINILIB)libmlx.a .
			ar rc $(NAME).a $(OBJS) get_next_line.o get_next_line_utils.o

comp:		all
			gcc $(CFLAGS) main.c $(NAME).a $(LIBFT)libft.a libmlx.a -o $(NAME) -framework OpenGL -framework AppKit

launch:		comp
			./Cube3D $(MAP1) 

minilib:	
			@make -C $(MINILIB)

libft:
			@make -C $(LIBFT) re

$(OBJS):	$(INCLUDES)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all