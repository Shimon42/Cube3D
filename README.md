# Cube 3D • Alpha 0.8.1 - Norming in progress

![Cube3D Screenshot](/images/sprites.png)

![Cube3D Minimap expanded](/images/minimap.png)

<hr>

-> make - Compile only

-> make launch - Compile changes & launch

<hr>

<kbd>ESC</kbd> - Quit (brutal killing)

<kbd>F</kbd> - Expand map

<kbd>Z</kbd> - Move forward

<kbd>S</kbd> - Move backward

<kbd>A</kbd> - Move Left

<kbd>D</kbd> - Move Right

<kbd>LEFT</kbd> <kbd>RIGHT</kbd> - Rotate camera (+ <kbd>SHIFT</kbd> to rotate/10)

<kbd>SPACE</kbd> - Jump

<hr>

	————————————————————————————————————
		Changes:
	———————————————————————————————————— 
	- All srcs normed except for draw_rect(), draw_walls(), init_sprite(), draw_sprite()

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- All srcs normed except for draw_rect(), draw_walls(), init_sprite(), draw_sprite()
	- Map parsing
	- Draw walls (fish eye sort of corrected)
	- Floor texture (Fisheye with some texture)
	- Wall Texture
	- Walls Collisions
	- Textured sprites
	- Sprites Collisions
	- Minimap display
	- SkyBox
	
	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	General
	- RANDOM CRASH ON START (Temporaly Fixed with -gcc g -g3 -fsanitize=address in Makefile)
	- Random BadMap error - weird chars in map display

	Drawing: 
	- Line drawn after end of win width is drawn on the other side of the window
	
	Moving:
	- Double speed if walk on side and move forward

	Floor Casting
	- Floor texture move badly sometimes
	- Fish eye

	Sprites:
	- Cropped sprite sometimes


![Cube3D Minimap expanded](/images/Bugs/sprites.png)
