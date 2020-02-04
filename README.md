# Cube 3D • Alpha 0.2.3

-> make - Compile only

-> make launch - Compile changes & launch


[ESC] - quit (brutal killing)

[F] - expand map

	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Closest grid x and y is detected and displayed on minimap
	- Correct draw_rect (size was size + 1) (Not sure 100%)
	- Cur pos in grid (yellow square on the minimap)

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Detect closest grid (Horizontal and Vertical)
	- Minimap display
	- Player and direction can be displayed

	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	- Line drawn after end of win width is drawn on the other side of the window
	- Player speed is different depending on the angle
