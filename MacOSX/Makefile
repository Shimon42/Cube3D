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
			$(SRCSPATH)Canvas/line/calc_first_quad.c \
			$(SRCSPATH)Canvas/line/calc_second_quad.c \
			$(SRCSPATH)Canvas/line/calc_third_quad.c \
			$(SRCSPATH)Canvas/line/calc_fourth_quad.c \
			$(SRCSPATH)Canvas/line/draw_line.c \
			$(SRCSPATH)Canvas/rect.c \
			$(SRCSPATH)Canvas/circle.c \
			$(SRCSPATH)Canvas/text.c \
			$(SRCSPATH)Canvas/context.c \
			$(SRCSPATH)Canvas/points.c \
			\
			$(SRCSPATH)Utils/colors.c \
			$(SRCSPATH)Utils/fps_counter.c \
			\
			$(SRCSPATH)Checker/check.c \
			$(SRCSPATH)Checker/flag_get.c \
			$(SRCSPATH)Checker/flag_get_utils.c \
			\
			$(SRCSPATH)Map/open_map.c \
			$(SRCSPATH)Map/map_debug.c \
			$(SRCSPATH)Map/init_map.c \
			$(SRCSPATH)Map/map_utils.c \
			$(SRCSPATH)Map/drawing/draw_fullmap.c \
			$(SRCSPATH)Map/drawing/draw_map_debug.c \
			$(SRCSPATH)Map/drawing/draw_map_utils.c \
			$(SRCSPATH)Map/drawing/draw_minimap.c \
			\
			$(SRCSPATH)Casting/wall_detect.c \
			$(SRCSPATH)Casting/draw_walls.c \
			$(SRCSPATH)Casting/floor_detect.c \
			$(SRCSPATH)Casting/draw_sky.c \
			\
			$(SRCSPATH)Sprites/new_sprite.c \
			$(SRCSPATH)Sprites/sprites_debug.c \
			$(SRCSPATH)Sprites/sprites_utils.c \
			$(SRCSPATH)Sprites/sprites.c \
			\
			$(SRCSPATH)Keys/keys_debug.c \
			$(SRCSPATH)Keys/keys_events.c \
			$(SRCSPATH)Keys/keys_states.c \
			\
			$(SRCSPATH)Player/player.c \
			$(SRCSPATH)Player/move.c \
			\
			$(SRCSPATH)create_bmp.c \
			\
			$(SRCSPATH)meditate.c \
			$(SRCSPATH)meditate_map.c \
			$(SRCSPATH)textures.c \
			$(DEBUGPATH)debug.c

GNL_SRCS =	$(INCPATH)Gnl/get_next_line.c \
			$(INCPATH)Gnl/get_next_line_utils.c

GNL_OBJS =	${GNL_SRCS:.c=.o}

CC =		gcc

CFLAGSPROD	= -g -Wall -Wextra -Werror
CFLAGS	= 
CFLAGSSAN	= -g -g3 -fsanitize=address -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

MAPS	= assets/maps/
LAB = $(MAPS)Lab.cub
WORLD = $(MAPS)world.cub
MAP = $(MAPS)map.cub
EMPTY = $(MAPS)empty.cub
MINE = $(MAPS)Mine.cub
NEW = $(MAPS)new_parse.cub
PAC = $(MAPS)pacman.cub

COL_TITLE = \033[2;33m
COL_CUBE = \033[2;32m
COL_TXT = \033[0;36m
COL_SHADOW = \033[2;36m

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			make -C $(MINILIB)
			make -C $(LIBFT)
			gcc -c $(GNL_SRCS) -D BUFFER_SIZE=400
			mv $(MINILIB)libmlx.a .
			mv $(LIBFT)libft.a .
			ar rc $(NAME).a $(OBJS) get_next_line.o get_next_line_utils.o

comp:		all
			gcc $(CFLAGSPROD) main.c $(NAME).a libft.a libmlx.a -o $(NAME) -framework OpenGL -framework AppKit

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
			@./$(NAME) $(NEW)

minilib:	
			@make -C $(MINILIB)

libft:
			@make -C $(LIBFT) re

$(OBJS):	$(INCLUDES)

clean:
			${RM} $(OBJS) get_next_line.o get_next_line_utils.o
			@make -C $(LIBFT) clean
			@make -C $(MINILIB) clean

fclean:		clean
			@make -C $(LIBFT) fclean
			@make -C $(MINILIB) clean
			${RM} $(NAME).a $(NAME) libft.a libmlx.a

re:			fclean all

.PHONY: clear