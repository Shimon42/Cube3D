# Cube 3D - Alpha 0.0.1

-> make - Compile only

-> make launch - Compile changes & launch


    ————————————————————————————————————
    	Changes:
    ————————————————————————————————————
	- Base Project folders
	- t_brain, t_ctx, t_point
	- draw_line() (don't work)

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Open new window

	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	- Weird bug with compiling not always working
		-> Need to rm "-framework OpenGL -framework AppKit" from Makefile
		-> make launch
		-> re put "-framework OpenGL -framework AppKit" and re "make launch"