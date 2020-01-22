# Cube 3D • Alpha 0.1.0

-> make - Compile only

-> make launch - Compile changes & launch

-> [ESC] to quit (brutal killing)
   
   
    ————————————————————————————————————
    	Changes:
    ————————————————————————————————————
	- Map parsing
	- Minimap draw
	- Add t_player, t_camera
	- Add static context for t_ctx functions line(), rect()
		-> no more need to precise context after context init
	- Add init_player()

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Open new window
	- [ESC] to quit (brutal killing)
	- Map parsing, without config
	- Minimap display

	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	- init_player -> SEGFAULT