NAME =		Cube3D

SRCSPATH =	srcs/
INCPATH =	includes/

MINILIB =	$(INCPATH)MiniLib/

INCLUDES =	$(INCPATH)cube3d.h \
			$(INCPATH)points.h \
			\
			$(MINILIB)mms/mlx.h \
			$(MINILIB)opengl/mlx.h \
			$(MINILIB)opengl/mlx_new_window.h \
			$(MINILIB)opengl/mlx_opengl.h \
			$(MINILIB)opengl/mlx_png.h \
			$(MINILIB)opengl/mlx_int.h \
			\
			debug.h


SRCS = 		main.c \
			$(SRCSPATH)draw_line.c \
			debug.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			@make -C $(MINILIB)mms
			@make -C $(MINILIB)opengl
			@cp $(MINILIB)opengl/libmlx.a $(NAME).a
			ar rc $(NAME).a $(OBJS)

comp:		all
			@gcc $(CFLAGS) main.c $(NAME).a -o $(NAME)  -framework OpenGL -framework AppKit

launch:		comp
			./Cube3D

minilib:	
			@make -C $(MINILIB)mms
			@make -C $(MINILIB)opengl

$(OBJS):	$(INCLUDES)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all