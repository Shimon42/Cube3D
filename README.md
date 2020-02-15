# Cube 3D • Alpha 0.4.0

![Cube3D Screenshot](/images/screen3.png)

-> make - Compile only

-> make launch - Compile changes & launch


[ESC] - quit (brutal killing)

[F] - expand map

[Z] - Move forward

[S] - Move backward

[A] - Move Left

[D] - Move Right

[LEFT] [RIGHT] - Rotate camera ( + [SHIFT] to rotate/10)

![Cube3D Minimap expanded](/images/screen2.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Draw Wall OK !
	- Draw fov on map

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
	- One line appear in center of screen for angles 0, 90, 180
	- Double speed if walk on side and move forward
