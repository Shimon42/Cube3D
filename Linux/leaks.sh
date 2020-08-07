#!bin/sh

EXEC=Cub3D
ARGS=assets/maps/new_parse.cub
SAVE=--save
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrin.log ./$EXEC $ARGS #$SAVE
grep -A1 "valgrind" valgrin.log | grep $EXEC
