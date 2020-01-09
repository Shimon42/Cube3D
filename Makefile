NAME =		Cube3D

SRCPATH =	srcs/
INCPATH =	includes/

MINILIB =	$(INCPATH)MiniLib/

INCLUDES =	$(INCPATH)cube3d.h \
			\
			$(MINILIB)mms/mlx.h \
			$(MINILIB)opengl/mlx.h \
			$(MINILIB)opengl/mlx_new_window.h \
			$(MINILIB)opengl/mlx_opengl.h \
			$(MINILIB)opengl/mlx_png.h \
			$(MINILIB)opengl/mlx_int.h \


SRCS = 		main.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -framework OpenGL -framework AppKit

OBJS = ${SRCS:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			@make -C $(MINILIB)mms
			@make -C $(MINILIB)opengl
			@cp $(MINILIB)opengl/libmlx.a $(NAME).a
			ar rc $(NAME).a $(OBJS)

comp:		all
			@gcc $(CFLAGS) main.c $(NAME).a -o $(NAME)

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