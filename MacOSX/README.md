# Cube 3D • Alpha 0.8.5 - All sources normed

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
	- All srcs normed, includes left

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- All srcs normed
	- Map parsing
	- Minimap display and expand to fullmap
	- Draw walls (fish eye sort of corrected)
	- SkyBox
	- Walls textures
	- Walls collisions
	- Floor texture (Fisheye with some texture)
	- Textured sprites
	- Sprites collisions
	
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
	- Weird position (Bad fish eye correction ?)
