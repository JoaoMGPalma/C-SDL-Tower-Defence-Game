#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <random>
#include "Background.h"
#include "GameManager.h"
#include "DrawText.h"


int main(){
    int windowWidth=800;
    int windowHeight=600;
	int tileSize=8;

	int currentWave;

	// Colors...
	SDLColor backColor(0,0,0,255);
	SDLColor foreColor(255,255,255,255);

	// Window...
	std::string windowTitle="TD Legolas - Defend the castle";
	SDLWindow window(windowWidth,windowHeight, windowTitle, backColor, foreColor);

	Texture frameTex = window.readFile("assets/frameSprite.png");

    GameManager game;
	bool running=true;
    while(running){


        window.clearWindow(backColor);

        /*********** LOAD TEXTURES ***************/
        game.loadAssets(window);
		/********** READ USER INPUTS... **********/
		window.updateInputs();
		if(window.quitRequested)
			running=false;

        window.updateInputs();

        SDLPoint mp = window.getMousePosition();

		/********* DRAW BACKGROUND ***************/
		drawBackground(window, tileSize, windowWidth, windowHeight);

        if(game.isWaveEnd()){
            game.spawnWave();
            currentWave++;
        }

        if(!game.isGameEnd())
            game.updateObjects();
        if(game.isGameEnd())
             drawText(window, "GAME OVER!", (windowWidth/2)-200, (windowHeight/2), 8, foreColor);


        window.renderTexture(frameTex, 0, 0, 255, 0);
        game.drawObjects(window, mp.x, mp.y);

        drawText(window, "move Left   A", 10, 160, 2, foreColor);
        drawText(window, "move right  D", 10, 180, 2, foreColor);
        drawText(window, "aim         MOUSE", 10, 200, 2, foreColor);
        drawText(window, "shoot       SPACE", 10, 220, 2, foreColor);

        if(game.isGameEnd())
             drawText(window, "GAME OVER!", (windowWidth/2)-200, (windowHeight/2), 8, foreColor);
        window.setColor(SDLColor(143, 143, 143, 255));


        window.render();
    }
    return 0;
}
