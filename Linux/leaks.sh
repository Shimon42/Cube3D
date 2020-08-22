#!bin/sh

EXEC=cub3D
ARGS=assets/maps/new_parse.cub
SAVE=--save
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --leak-resolution=high --show-reachable=yes --track-origins=yes ./$EXEC $ARGS #$SAVE
