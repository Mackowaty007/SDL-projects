#pragma once

void setTheObjectScale(){
	for (int i=0;i<LEN(vertecies);i++){
		for (int c=0;c<LEN(vertecies[0]);c++){
			vertecies[i][c] *= -100;
		}
	}
}

//should have done this in the converter file but text operations are hard
void decrementAllTheVerteciesValuesByOne(){
	for (int i=0;i<LEN(polygons);i++){
		for (int c=0;c<LEN(polygons[0]);c++){
			polygons[i][c] --;
		}
	}
}

float cutANumber(float number,float max,float min){
	if (number>max){
		number=max;
	}
	if (number<min){
		number=min;
	}
	return number;
}

void handleInput(){
	SDL_Event ev;
    while( SDL_PollEvent( &ev ) )
    {
        if( ( SDL_QUIT == ev.type ) ||
            ( SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode ) )
        {
            running = false;
            break;
        }
    }
/*
	//rotate the player
	if (kHeld & KEY_A || kHeld & KEY_CSTICK_RIGHT)
		playerRot[0] -= rotSpeed;//*deltaTime;
	if (kHeld & KEY_Y || kHeld & KEY_CSTICK_LEFT)
		playerRot[0] += rotSpeed;//*deltaTime;
	if (kHeld & KEY_X || kHeld & KEY_CSTICK_UP)
		playerRot[1] += rotSpeed;//*deltaTime;
	if (kHeld & KEY_B || kHeld & KEY_CSTICK_DOWN)
		playerRot[1] -= rotSpeed;//*deltaTime;

	playerRot[1] = cutANumber(playerRot[1],PI,0);

	if(playerRot[0]>PI){
		playerRot[0] -= 2*PI;
	}
	if(playerRot[0]<-PI){
		playerRot[0] += 2*PI;
	}
	if(playerRot[1]>PI){
		playerRot[1] -= 2*PI;
	}
	if(playerRot[1]<-PI){
		playerRot[1] += 2*PI;
	}

	//move the player
	//fowards and backwards
	playerPos[0] += sin(playerRot[0])*circlePadPos.dy*playerSpeed;//*deltaTime;
	playerPos[2] += cos(playerRot[0])*circlePadPos.dy*playerSpeed;//*deltaTime;
	//side to side
	playerPos[0] -= sin(playerRot[0]+PI/2)*circlePadPos.dx*playerSpeed;//*deltaTime;
	playerPos[2] -= cos(playerRot[0]+PI/2)*circlePadPos.dx*playerSpeed;//*deltaTime;

	//move the player up and down
	if (kHeld & KEY_R)
		playerPos[1] -= playerSpeed*154;//*deltaTime;
	if (kHeld & KEY_L)
		playerPos[1] += playerSpeed*154;//*deltaTime;
    */
}