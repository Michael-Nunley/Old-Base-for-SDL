#include "main.h"
#include "globals.h"

#include "window.h"
#include "texture.h"
#include "timer.h"

#include "tilesheet.h"
#include "button.h"

#include "init.h"

const int TOTAL_BUTTONS = 2;
const int TOTAL_BACKGROUND_TILES = 1;
LButton gButtons[TOTAL_BUTTONS];
Tile gTiles[TOTAL_BACKGROUND_TILES];

LTexture gPicTexture;

Sint32 gMapData[2500];

SDL_RWops* map_01 = SDL_RWFromFile("maps/01.six", "r+b");

//gFont = TTF_OpenFont("lazy.ttf", 16);

#include "close.h"

bool loadMedia()
{
	bool success = true;
/*
	if(map_01 == NULL)
	{
		printf("Warning: Unable to open map_01! SDL Error: %s\n", SDL_GetError());

		//Create map_01 for writing

		map_01 = SDL_RWFromFile("maps/01.six", "w+b");
		if(map_01 != NULL)
		{
			printf("New map_01 created!\n");

			//Initialize data
			for(int i = 0; i < 2500; ++i)
			{
				gMapData[i] = 0;
				SDL_RWwrite(map_01, &gMapData[i], sizeof(Sint32), 1);
			}

			//Close map_01 handler
			SDL_RWclose(map_01);
		}
		else {printf("Error: Unable to create map_01! SDL Error: %s\n", SDL_GetError()); success = false;}

	}
*/
/*
	if(gFont == NULL)
        {printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError()); success = false;}
    */
	if(!gPicTexture.loadFromFile("sprites/tile13.gif"))
        {printf("Failed to load test texture!\n"); success = false;}
	if(!gButtonSpriteSheetTexture.loadFromFile("sprites/button.png"))
        {printf("Failed to load button sprite texture!\n"); success = false;}
	else
	{
		for(int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 200;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}
	}
	if(!gBackgroundSpriteSheetTexture.loadFromFile("sprites/Grasslands_A.png"))
        {printf("Failed to load background a sprite texture!\n"); success = false;}
	else
	{
	    int x = 0;
		for(int i = 0; i < 31; ++i)
		{
		    x++;
		    gBackgroundSprite[x].x = 0;
			gBackgroundSprite[x].y = i * 16;
			gBackgroundSprite[x].w = 16;
			gBackgroundSprite[x].h = 16;
		}
		//x += 31;
		for(int i = 0; i < 18; ++i)
		{
		    x++;
			gBackgroundSprite[x].x = i * 16;
			gBackgroundSprite[x].y = 0;
			gBackgroundSprite[x].w = 16;
			gBackgroundSprite[x].h = 16;
		}
	}
	return success;
}

int main(int argc, char* args[])
{
	if(!init()) {printf("Failed to initialize!\n");}
	else
	{
		if(!loadMedia()) {printf("Failed to load media!\n");}
		else
		{
			SDL_Event e;

			int x,y;
            gButtons[0].setPosition                           (0, 0);
            gButtons[0].isExitButton =                          true;
            gButtons[1].setPosition (SCREEN_WIDTH - BUTTON_WIDTH, 0);
            gButtons[1].isExitButton =                         false;
            bool fug = true;

			while(!quit)
			{
			    if (!escapeOpen)
                {
                    SDL_GetMouseState(&x,&y);
                }
				while(SDL_PollEvent(&e) != 0)
				{
				    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_ESCAPE: escapeOpen = !escapeOpen; break;
                        }
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && escapeOpen == false)
                    {
                        switch(e.button.button)
                        {
                            case SDL_BUTTON_LEFT: fug = !fug;
                        }
                    }
					if(e.type == SDL_QUIT) {quit = true;}
					gWindow.handleEvent(e);
					if (escapeOpen)
                    {
                        for(int i = 0; i < TOTAL_BUTTONS; ++i)
                        {
                            gButtons[i].handleEvent(&e);
                        }
                    }
				}
				if(gWindow.hasKeyboardFocus())
				{
                    //Clear screen
                    if (fug)
                    {
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                    }

                    gPicTexture.render(x,y);

                    if (escapeOpen)
                    {
                        for(int i = 0; i < TOTAL_BUTTONS; ++i)
                        {
                            gButtons[i].render();
                        }
                    }

                    //Update screen
                    SDL_RenderPresent(gRenderer);
				}
			}
		}
	}

	close();
	return 0;
}
