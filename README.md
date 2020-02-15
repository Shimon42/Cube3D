# Cube 3D • Alpha 0.4.1

![Cube3D Screenshot](/images/textured.png)

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
	- Begin of walls textures
	- Begin of wall shadow gest

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (bad orientation display sometimes + fish eye)
	- Wall Texture (Bad scaled & texture isn't attached to block)
	- Minimap display
	
	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	Drawing: 
	- Line drawn after end of win width is drawn on the other side of the window
	- One line appear in center of screen for angles 0, 90, 180
	
	Moving:
	- Double speed if walk on side and move forward

	Textures:
	- Only work with one texture (problem with texture malloc)
	- Bad texture scale
