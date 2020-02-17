# Cube 3D • Alpha 0.4.2

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
	- Add FPS counter
	- Fixed "texture isn't 'attached' to block" bug
	- Better init_buff (More generic)

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (fish eye sort of corrected)
	- Wall Texture (Bad scaled)
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
