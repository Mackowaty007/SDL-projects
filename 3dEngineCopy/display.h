SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
SDL_RenderClear( renderer );

//draw vertexes
    //declaring usefull variables (they calculate the angle from the players view to vertexes)
float angleToPoint[4][2];
float angleDifference[4][2];

//calculate all the angles
//do this for every vertex of the square
for(int i=0;i<LEN(polygons);i++){
	unsigned int currentVertecie;
	unsigned short int howManyPoinstToCalculate = 3;
	//check if you should calculate 4 or 3 vertecies
	if (polygons[i][3] != -1){
		howManyPoinstToCalculate = 4;
	}
	else{
		howManyPoinstToCalculate = 3;
	}
	//calculate the angle tocalculate the angle from the center of the screen to the vertex a vertecies verticy
	for(currentVertecie=0;currentVertecie<howManyPoinstToCalculate;currentVertecie++){
		if(vertecies[polygons[i][currentVertecie]][1]-playerPos[1]>=0){
			angleToPoint[currentVertecie][1] = atan((sqrt(pow(vertecies[polygons[i][currentVertecie]][2]-playerPos[2],2)+pow(vertecies[polygons[i][currentVertecie]][0]-playerPos[0],2)))/(vertecies[polygons[i][currentVertecie]][1]-playerPos[1]));
		}
		else{
			angleToPoint[currentVertecie][1] = atan((sqrt(pow(vertecies[polygons[i][currentVertecie]][2]-playerPos[2],2)+pow(vertecies[polygons[i][currentVertecie]][0]-playerPos[0],2)))/(vertecies[polygons[i][currentVertecie]][1]-playerPos[1]))+PI;
		}
		if(vertecies[polygons[i][currentVertecie]][2]-playerPos[2]>=0){
			angleToPoint[currentVertecie][0] = atan((vertecies[polygons[i][currentVertecie]][0]-playerPos[0])/(vertecies[polygons[i][currentVertecie]][2]-playerPos[2]));
		}
		else{
			angleToPoint[currentVertecie][0] = atan((vertecies[polygons[i][currentVertecie]][0]-playerPos[0])/(vertecies[polygons[i][currentVertecie]][2]-playerPos[2]))+PI;
		}
		if(angleToPoint[currentVertecie][0]>PI){
			angleToPoint[currentVertecie][0] -= 2*PI;
		}
		if(angleToPoint[currentVertecie][0]<-PI){
			angleToPoint[currentVertecie][0] += 2*PI;
		}
		if(angleToPoint[currentVertecie][1]>PI){
			angleToPoint[currentVertecie][1] -= 2*PI;
		}
		if(angleToPoint[currentVertecie][1]<-PI){
			angleToPoint[currentVertecie][1] += 2*PI;
		}
		angleDifference[currentVertecie][0] = playerRot[0]-angleToPoint[currentVertecie][0];
		if(angleDifference[currentVertecie][0]>PI){
			angleDifference[currentVertecie][0] -= 2*PI;
		}
		if(angleDifference[currentVertecie][0]<-PI){
			angleDifference[currentVertecie][0] += 2*PI;
		}
		angleDifference[currentVertecie][1] = playerRot[1]-angleToPoint[currentVertecie][1];
		if(angleDifference[currentVertecie][1]>PI){
			angleDifference[currentVertecie][1] -= 2*PI;
		}
		if(angleDifference[currentVertecie][1]<-PI){
			angleDifference[currentVertecie][1] += 2*PI;
		}
	}

    #ifdef DRAW_FACES
    //check if the face should be culled or not
    double result = atan2(angleDifference[2][1] - angleDifference[0][1], angleDifference[2][0] - angleDifference[0][0]) - atan2(angleDifference[1][1] - angleDifference[0][1], angleDifference[1][0] - angleDifference[0][0]);
    //makes it impossible for the result to be negative
    if (result < 0){
        result += 2*PI;
    }
    if(result < 0 || result > PI){
        //check the distance to a polygon
        float distanceToPolygon = -sqrt(pow(playerPos[0]-vertecies[polygons[i][currentVertecie]][0],2) + pow(playerPos[1]-vertecies[polygons[i][currentVertecie]][1],2) + pow(playerPos[2]-vertecies[polygons[i][currentVertecie]][2],2));

        std::vector< SDL_Vertex > verts =
        {
            { SDL_FPoint{ 
            SCREEN_WIDTH /2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
            SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV
            }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ 
            SCREEN_WIDTH /2 + (angleDifference[1][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
            SCREEN_HEIGHT/2 + (angleDifference[1][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV 
            }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ 
            SCREEN_WIDTH /2 + (angleDifference[2][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
            SCREEN_HEIGHT/2 + (angleDifference[2][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV 
            }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
        };
        //fun with colors
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );

        //if the polygon has 4 sides draw another triangle
        if (polygons[i][3] != -1){
            std::vector< SDL_Vertex > verts =
            {
                { SDL_FPoint{ 
                SCREEN_WIDTH /2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
                SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV
                }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
                { SDL_FPoint{ 
                SCREEN_WIDTH /2 + (angleDifference[3][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
                SCREEN_HEIGHT/2 + (angleDifference[3][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV
                }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
                { SDL_FPoint{ 
                SCREEN_WIDTH /2 + (angleDifference[2][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
                SCREEN_HEIGHT/2 + (angleDifference[2][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV
                }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
            };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
            SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
        }
    }
    #endif
    /*
    #ifdef DRAW_LINES
    C2D_DrawLine(
    SCREEN_WIDTH /2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    SCREEN_WIDTH /2 + (angleDifference[1][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[1][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    LINE_WIDTH,0);
    C2D_DrawLine(
    SCREEN_WIDTH /2 + (angleDifference[2][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[2][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    SCREEN_WIDTH /2 + (angleDifference[1][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[1][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    LINE_WIDTH,0);
    C2D_DrawLine(
    SCREEN_WIDTH /2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    SCREEN_WIDTH /2 + (angleDifference[2][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[2][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
    LINE_WIDTH,0);
    //draw additional lines if a face has 4 corners
    if (polygons[i][3] != -1){
        C2D_DrawLine(
        SCREEN_WIDTH /2 + (angleDifference[3][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
        SCREEN_HEIGHT/2 + (angleDifference[3][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
        SCREEN_WIDTH /2 + (angleDifference[2][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
        SCREEN_HEIGHT/2 + (angleDifference[2][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,lineColor,
        LINE_WIDTH,0);
    }
    #endif*/
    #ifdef DRAW_VERTECIES
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderDrawPoint(renderer,
    SCREEN_WIDTH/2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,
    SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV);
    //C2D_DrawRectSolid(SCREEN_WIDTH/2 + (angleDifference[0][0])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,SCREEN_HEIGHT/2 + (angleDifference[0][1])*(SCREEN_WIDTH/SCREEN_HEIGHT)*FOV,0,POINT_SIZE,POINT_SIZE, vertexColor);
    #endif
}
SDL_RenderPresent( renderer );