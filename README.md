# Cube 3D • Alpha 0.6.4

![Cube3D Screenshot](/images/world.png)

-> make - Compile only

-> make launch - Compile changes & launch


<kbd>ESC</kbd> - Quit (brutal killing)

<kbd>F</kbd> - Expand map

<kbd>Z</kbd> - Move forward

<kbd>S</kbd> - Move backward

<kbd>A</kbd> - Move Left

<kbd>D</kbd> - Move Right

<kbd>LEFT</kbd> <kbd>RIGHT</kbd> - Rotate camera ( + <kbd>SHIFT</kbd> to rotate/10)

<kbd>UP</kbd> - Maxi FOV

<kbd>SPACE</kbd> - Jump (WYP)


![Cube3D Minimap expanded](/images/minimap.png)


	————————————————————————————————————
		Changes:
	————————————————————————————————————
	- No more texture bug
	- No more random segfault at start

    ————————————————————————————————————
		Cur State:
	————————————————————————————————————
	- Map parsing, without config
	- Draw walls (fish eye sort of corrected)
	- Floor texture (Fisheye with some texture)
	- Wall Texture
	- Walls Collisions
	- Minimap display
	- SkyBox
	
	————————————————————————————————————
    	Known Bugs:
	————————————————————————————————————
	Drawing: 
	- Line drawn after end of win width is drawn on the other side of the window
	
	Moving:
	- Double speed if walk on side and move forward

