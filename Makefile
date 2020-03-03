NAME =		Cub3D

SRCSPATH =	srcs/
DEBUGPATH =	debug/
INCPATH =	includes/

#---------  LIBS --
MINILIB =	$(INCPATH)MiniLib/
LIBFT =		$(INCPATH)Libft/

#---------	INCLUDES --
INCLUDES =	$(INCPATH)cube3d.h \
			$(INCPATH)my_canvas.h \
			$(INCPATH)map.h \
			$(INCPATH)player.h \
			$(INCPATH)Gnl/get_next_line.h \
			$(LIBFT)includes/libft.h \
			\
			$(MINILIB)mlx.h \
			\
			$(DEBUGPATH)debug.h\
			$(DEBUGPATH)debug_defines.h

#--------	SRCS --
SRCS = 		main.c \
			$(SRCSPATH)Canvas/draw_line.c \
			$(SRCSPATH)Canvas/rect.c \
			$(SRCSPATH)Canvas/circle.c \
			$(SRCSPATH)Canvas/text.c \
			$(SRCSPATH)Canvas/context.c \
			$(SRCSPATH)map_parsing.c \
			$(SRCSPATH)draw_map.c \
			$(SRCSPATH)wall_detect.c \
			$(SRCSPATH)sprites.c \
			$(SRCSPATH)player.c \
			$(DEBUGPATH)debug.c

GNL_SRCS =	$(INCPATH)Gnl/get_next_line.c \
			$(INCPATH)Gnl/get_next_line_utils.c

GNL_OBJS =	${GNL_SRCS:.c=.o}

CC =		gcc

CFLAGSz	= -Wall -Wextra -Werror
CFLAGS	= 

OBJS = ${SRCS:.c=.o}

MAPS	= assets/maps/
MAP1 = $(MAPS)map.cub
MAP2 = $(MAPS)map2.cub
EMPTY = $(MAPS)empty.cub

COL_TITLE = \033[2;33m
COL_CUBE = \033[2;32m
COL_TXT = \033[0;36m
COL_SHADOW = \033[2;36m

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			make -C $(MINILIB)
			make -C $(LIBFT)
			gcc -c $(GNL_SRCS) -D BUFFER_SIZE=128
			mv $(MINILIB)libmlx.a .
			mv $(LIBFT)libft.a .
			ar rc $(NAME).a $(OBJS) get_next_line.o get_next_line_utils.o

comp:		all
			gcc $(CFLAGS) main.c $(NAME).a libft.a libmlx.a -o $(NAME) -framework OpenGL -framework AppKit

launch:		comp
			clear
			@echo "$(COL_CUBE)  .–––––––––––––––––––––––––––––––––––––––––––––––––––––––––.	"
			@echo " / |                     $(COL_TITLE)Launching$(COL_CUBE)                          | \	"
			@echo "+––+––––––––––––––––––––––––––––––––––––––––––––––––––––––––+––+"
			@echo "|  |$(COL_TXT)             _____       _       _____ ____$(COL_CUBE)             |  |"
			@echo "|  |$(COL_TXT)            /  __ \     | |     |____ |  _  \ $(COL_CUBE)          |  |"
			@echo "|  |$(COL_TXT)           |  /  \/_   _| |__       / / | | |$(COL_CUBE)           |  |"
			@echo "|  |$(COL_TXT)           |  |   | | | | |_ \      \ \ | | |$(COL_CUBE)           |  |"
			@echo "|  |$(COL_TXT)           |  \__/\ |_| | |_) | ____/ / |_/ /$(COL_CUBE)           |  |"
			@echo "|  |____________$(COL_TXT)\_____/\____|____/  \____/|____/ $(COL_CUBE)___________|  |"
			@echo "| / $(COL_SHADOW)           /////// /////////     \\\\\\\\\\\\\\\\\\\ \\\\\\\\\\\\\\\\\\\\\\\\$(COL_CUBE)            \ |"
			@echo "+––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––+\033[0m"
			@./$(NAME) $(EMPTY)

minilib:	
			@make -C $(MINILIB)

libft:
			@make -C $(LIBFT) re

$(OBJS):	$(INCLUDES)

clean:
			${RM} $(OBJS) get_next_line.o get_next_line_utils.o

fclean:		clean
			${RM} $(NAME).a $(NAME) libft.a libmlx.a

re:			fclean all

.PHONY: clear