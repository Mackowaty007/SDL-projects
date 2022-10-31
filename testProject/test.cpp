#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define GRID_SIZE 50

int close = 0;
bool isGameOver = false;
int enemyPos[2] = {rand()%SCREEN_WIDTH/GRID_SIZE,rand()%SCREEN_HEIGHT/GRID_SIZE};
int snakeHeading = 0;
std::vector<std::vector<int>> snakeBodyPos = 
{
	{(SCREEN_WIDTH/GRID_SIZE)/2  ,(SCREEN_HEIGHT/GRID_SIZE)/2},
	{(SCREEN_WIDTH/GRID_SIZE)/2  ,(SCREEN_HEIGHT/GRID_SIZE)/2},
	{(SCREEN_WIDTH/GRID_SIZE)/2  ,(SCREEN_HEIGHT/GRID_SIZE)/2},
	{(SCREEN_WIDTH/GRID_SIZE)/2  ,(SCREEN_HEIGHT/GRID_SIZE)/2},
};
struct{
    int r = 110;
    int g = 230;
    int b = 40;
}snakeColor;
struct{
    int r = 200;
    int g = 33;
    int b = 10;
}fruitColor;

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
 

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface* surface;
    surface = IMG_Load("2guys1chopper.jpg");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
 
    // animation loop
    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    snakeHeading = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    snakeHeading = 3;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    snakeHeading = 2;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    snakeHeading = 4;
                    break;
                default:
                    break;
                }
            }
        }
  
        //printf("%i",snakeBodyPos.size());
        //std::cout << snakeBodyPos.size() << std::endl;
        for (int i=snakeBodyPos.size()-1;i>=1;i--){
			snakeBodyPos[i][0] = snakeBodyPos[i-1][0];
			snakeBodyPos[i][1] = snakeBodyPos[i-1][1];
		}

		//move snakes head
		switch(snakeHeading){
			case 1:
				snakeBodyPos[0][1] --;
				break;
			case 2:
				snakeBodyPos[0][1] ++;
				break;
			case 3:
				snakeBodyPos[0][0] --;
				break;
			case 4:
				snakeBodyPos[0][0] ++;
				break;
		}

		//limit the snake head pos
		if(snakeBodyPos[0][0]>=SCREEN_WIDTH/GRID_SIZE){
			snakeBodyPos[0][0] = 0;
		}
		else if(snakeBodyPos[0][1]>=SCREEN_HEIGHT/GRID_SIZE){
			snakeBodyPos[0][1] = 0;
		}
		else if(snakeBodyPos[0][0]<0){
			snakeBodyPos[0][0] = SCREEN_WIDTH/GRID_SIZE-1;
		}
		else if(snakeBodyPos[0][1]<0){
			snakeBodyPos[0][1] = SCREEN_HEIGHT/GRID_SIZE-1;
		}
			
		//add a body part if it colides with an enemy
		if(snakeBodyPos[0][0]==enemyPos[0] && snakeBodyPos[0][1]==enemyPos[1]){
			//generate random enemy pos
			enemyPos[0] = rand()%SCREEN_WIDTH /GRID_SIZE;
			enemyPos[1] = rand()%SCREEN_HEIGHT/GRID_SIZE;
			
			//add a new body part
            for(int x=0;x>snakeBodyPos.size();x++){
                for(int x=0;x>snakeBodyPos.size();x++){
                    std::cout << snakeBodyPos.size() << std::endl;
                }
            }
            
			snakeBodyPos.push_back(std::vector<int> {snakeBodyPos[snakeBodyPos.size()][0],snakeBodyPos[snakeBodyPos.size()][1]});
			//set the new body part to the last body part position
			//snakeBodyPos[snakeBodyPos.size()].push_back(snakeBodyPos[snakeBodyPos.size()-1][0]);
			//snakeBodyPos[snakeBodyPos.size()].push_back(snakeBodyPos[snakeBodyPos.size()-1][1]);
		}
		//check if the snake is coliding with itself
		if(snakeHeading !=0){
			for (unsigned int i=1;i<snakeBodyPos.size();i++){
				if(snakeBodyPos[0][0] == snakeBodyPos[i][0] && snakeBodyPos[0][1] == snakeBodyPos[i][1]){
					isGameOver = true;
				}
			}
		}

        SDL_RenderClear(rend);

        //draw snake body
		for(unsigned int i = 0;i<snakeBodyPos.size();i++){
            SDL_Rect snakeBodyPart;
            snakeBodyPart.x = snakeBodyPos[i][0]*GRID_SIZE;
            snakeBodyPart.y = snakeBodyPos[i][1]*GRID_SIZE;
            snakeBodyPart.w = GRID_SIZE;
            snakeBodyPart.h = GRID_SIZE;
            SDL_SetRenderDrawColor(rend, snakeColor.r, snakeColor.g, snakeColor.b, 255);
            SDL_RenderFillRect(rend, &snakeBodyPart);
		}
		//draw the good stuff
        //why does the snake eat fruit? I thought they were carbovores
		SDL_Rect fruit;
        fruit.x = enemyPos[0]*GRID_SIZE;
        fruit.y = enemyPos[1]*GRID_SIZE;
        fruit.w = GRID_SIZE;
        fruit.h = GRID_SIZE;
        SDL_SetRenderDrawColor(rend, fruitColor.r, fruitColor.g, fruitColor.b, 255);
        SDL_RenderFillRect(rend,&fruit);

		//draw game over screen
		if(isGameOver){
			//C2D_DrawSprite(&sprites[0].spr);
		}

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderPresent(rend);
        // calculates to 60 fps
        SDL_Delay(1000 / 10);
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}