//http://nicmendoza.github.io/playfuljs-demos/raycaster/

function(player,map,column,columnProps,sprites) {
	
	var ctx = this.ctx,
		left = Math.floor(column * this.spacing),
		width = Math.ceil(this.spacing),
		angle = this.fov * (column / this.resolution - 0.5),
		columnWidth = this.width / this.resolution,
		sprite,props,obj,textureX,height,projection, mappedColumnObj,spriteIsInColumn,top;

	//todo: make rays check for objects, and return those that it actually hit

	//check if ray hit an object
	//if(!columnProps.objects.length){return;}

	sprites = sprites.filter(function(sprite){
	 return !columnProps.hit || sprite.distanceFromPlayer < columnProps.hit;
	});


	for(var i = 0; i < sprites.length; i++){
		sprite = sprites[i];

		//mappedColumnObj = columnProps.objects.filter(function(obj){
		//	return sprite === obj.object;
		//})[0];

		//if(!mappedColumnObj)return;

		//determine if sprite should be drawn based on current column position and sprite width
		spriteIsInColumn =  left > sprite.render.cameraXOffset - ( sprite.render.width / 2 ) && left < sprite.render.cameraXOffset + ( sprite.render.width / 2 );

		//console.log(spriteIsInColumn);

		if(spriteIsInColumn){
			textureX = Math.floor( sprite.texture.width / sprite.render.numColumns * ( column - sprite.render.firstColumn ) );

			this.ctx.fillStyle = 'black';
			this.ctx.globalAlpha = 1;
			//ctx.fillRect(left, top , 10, sprite.render.height);

			var brightness = Math.max(sprite.distanceFromPlayer / this.lightRange - map.light, 0) * 100;

			sprite.texture.image.style.webkitFilter = 'brightness(' + brightness + '%)';
			sprite.texture.image.style.filter = 'brightness(' + brightness  + '%)';
			
			ctx.drawImage(sprite.texture.image, textureX, 0, 1, sprite.texture.height, left, sprite.render.top, width, sprite.render.height);



			

			//debugger;

			//ctx.fillRect(left, sprite.render.top, columnWidth, sprite.render.height);
			//debugger;

		}

		
	};

