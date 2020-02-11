# Cube 3D • Alpha 0.3.6

![Cube3D Screenshot](/images/screen3.png)

-> make - Compile only

-> make launch - Compile changes & launch


[ESC] - quit (brutal killing)

[F] - expand map

[Z] - Move forward

[S] - Move backward

[A] - Move Left

[D] - Move Right

[LEFT] [RIGHT] - Rotate camera ( + [SHIFT] - Rotate / 10)

![Cube3D Minimap expanded](/images/screen2.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Player spawn and direction
	- Draw wall is a little better
		-> Bad drawing on the left side when angle > 0

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (bad orientation display sometimes + fish eye)
	- Minimap display

	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	- Line drawn after end of win width is drawn on the other side of the window
