# Cube 3D • Alpha 0.7

![Cube3D Screenshot](/images/sprites.png)

-> make - Compile only

-> make launch - Compile changes & launch


<kbd>ESC</kbd> - Quit (brutal killing)

<kbd>F</kbd> - Expand map

<kbd>Z</kbd> - Move forward

<kbd>S</kbd> - Move backward

<kbd>A</kbd> - Move Left

<kbd>D</kbd> - Move Right

<kbd>LEFT</kbd> <kbd>RIGHT</kbd> - Rotate camera (+ <kbd>SHIFT</kbd> to rotate/10)

<kbd>SPACE</kbd> - Jump


![Cube3D Minimap expanded](/images/minimap.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- Draw sprites !!!! (Laggy when player is too close)
	- Sprites collisions
	- Fixed bad player move at start if no rotat first

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (fish eye sort of corrected)
	- Floor texture (Fisheye with some texture)
	- Wall Texture
	- Walls Collisions
	- Textured sprites [WIP]
	- Sprites Collisions
	- Minimap display
	- SkyBox
	
	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	General
	- Random Crash On Start
	- Random BadMap error - weird chars in map display

	Drawing: 
	- Line drawn after end of win width is drawn on the other side of the window
	
	Moving:
	- Double speed if walk on side and move forward

	Sprites
	- Bad start_y
	- Streched textures
	- Sprite is cropped sometimes

	Floor Casting
	- Floor texture move badly sometimes

![Cube3D Screenshot](/images/Bugs/sprites.png)
