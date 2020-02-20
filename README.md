# Cube 3D • Alpha 0.4.3

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

![Cube3D Minimap expanded](/images/minimap.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Gest hitbox sideway
	- Fixed "texture isn't 'attached' to block" bug
	
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
	- One line appear in center of screen for angles 0, 90, 180
	
	Moving:
	- Double speed if walk on side and move forward

	Textures:
	- Only work with one texture (problem with texture malloc)
