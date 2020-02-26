# Cube 3D • Alpha 0.5.0

![Cube3D Screenshot](/images/textured.png)

-> make - Compile only

-> make launch - Compile changes & launch


[ESC] - Quit (brutal killing)

[F] - Expand map

[Z] - Move forward

[S] - Move backward

[A] - Move Left

[D] - Move Right

[LEFT] [RIGHT] - Rotate camera ( + [SHIFT] to rotate/10)

[UP] - Maxi FOV

[SPACE] - Jump (WYP)


![Cube3D Minimap expanded](/images/minimap.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Fixed "FPS drop if too close from wall", only lose 5 FPS now

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (fish eye sort of corrected)
	- Wall Texture
	- Minimap display
	
	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	Drawing: 
	- Line drawn after end of win width is drawn on the other side of the window
	
	Moving:
	- Double speed if walk on side and move forward

