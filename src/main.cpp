#include "main.h"
#include "globals.h"

#include "window.h"
#include "texture.h"
#include "timer.h"

#include "button.h"
#include "frame.h"

#include "init.h"
/*******************************************/
std::chrono::milliseconds ms;

const int TOTAL_BUTTONS = 2;
const int TOTAL_BACKGROUND_TILES = 1;
LButton gButtons[TOTAL_BUTTONS];

const int total_stuff = 10000;
int stuffInUse = 0;

int totalNumberOfDots = 1;

int x,y;
double  targetTimeStep =     16.6666666667,
        lastTime1 =           0.0;
int64_t timeBehind1 =         0.0;

double  lastTime2 =           0.0;

double currentFPS = 0;
int64_t timeBehind2 =         0.0;

LTexture gPicTexture,
         gFPSTexture,
         gLagTexture[total_stuff];

Frame gFrame;
/*******************************************/

#include "close.h"

bool loadMedia()
{
    gFont = TTF_OpenFont("lazy.ttf", 16);
    gMusic = Mix_LoadMUS("audio/noise.wav");
	bool success = true;
	if(gFont == NULL)
        {printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError()); success = false;}
    else
	{
		SDL_Color textColor = {255, 255, 255};
		if(!gFPSTexture.loadFromRenderedText("60", textColor))
            {printf("Failed to render text texture!\n"); success = false;}
	}
	if(!gPicTexture.loadFromFile("sprites/tile13.gif"))
        {printf("Failed to load test texture!\n"); success = false;}
    for(int i = 0; i < total_stuff; i++)
    {
        if(!gLagTexture[i].loadFromFile("sprites/SinglePixel.png"))
        {printf("Failed to load lag texture!\n"); success = false;}
    }
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
	if(gMusic == NULL)
        {printf("Failed to load music! SDL_MIX Error: %s\n", Mix_GetError()); success = false;}
	//tilesheet
	/*if(!gBackgroundSpriteSheetTexture.loadFromFile("sprites/Grasslands_A.png"))
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
	}*/
	return success;
}

void updateOpen()
{
    currentFPS = (1000/lastTime1);




    if (currentFPS >= 29)
    {
        totalNumberOfDots++;
    }
    else
    {
        std::cout << currentFPS << "|" << totalNumberOfDots << std::endl;
        totalNumberOfDots--;
    }

    //Clear screen
    for(int i = 0; i < stuffInUse; i++)
    {
        gLagTexture[i].render(
            rand() %gWindow.getWidth(),
            rand() %gWindow.getHeight());
    }

    //gPicTexture.render(x,y); //put the random picture where your mouse is

    /* Only render the buttons if the escape menu is open */
    if(escapeOpen) {for(int i = 0; i < TOTAL_BUTTONS; ++i) {gButtons[i].render();}}

    //SDL_Color textColor = {0, 0, 0};
    //gFPSTexture.loadFromRenderedText(doubleToString(currentFPS) , textColor);
    //gFPSTexture.render(0,0);


    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    for(int i = 0; i < totalNumberOfDots; i++)
    {
        int swag1 = rand() %gWindow.getWidth(),swag2 = rand() %gWindow.getHeight();
        SDL_RenderDrawPoint(gRenderer, swag1, swag2);

    }
    SDL_RenderPresent(gRenderer); //Update screen
}

void updateClose()
{
    //std::cout << "closed";
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

			//initialize buttons and mouse position
            gButtons[0].isExitButton =                          true;
            gButtons[0].setPosition                           (0, 0);
            gButtons[1].setPosition (SCREEN_WIDTH - BUTTON_WIDTH, 0);
            gButtons[1].isExitButton =                         false;

            //Mix_PlayMusic(gMusic, -1);

			while(!quit)
			{
			    //std::cout << lastTime1 <<  "|" << lastTime2 << std::endl;
			    ms = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch());

                lastTime1 = -timeBehind1 + ms.count();
                if(lastTime1 >= targetTimeStep)
                {
                    timeBehind1 = ms.count();
                    //lastTime -= targetTimeStep;

                    if(!escapeOpen) {SDL_GetMouseState(&x,&y);}
                    if(gWindow.hasKeyboardFocus()) {updateOpen();}
                    else{updateClose();}
				}
				lastTime2 = -timeBehind2 + ms.count();
				if(lastTime2 >= 10)
                {
                    timeBehind2 = ms.count();
                    if(SDL_PollEvent(&e) != 0)
                    {
                        /* When you press escape, it shows a quit menu, pauses everything else going on */
                        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
                            {switch(e.key.keysym.sym)
                                //toggle the escape menu's visibility
                                {
                                    case SDLK_ESCAPE: escapeOpen = !escapeOpen; break;
                                    case SDLK_UP: targetTimeStep = 33.333333333; break;
                                    case SDLK_DOWN: targetTimeStep = 16.666666667; break;
                                }}
                        else if(e.type == SDL_MOUSEBUTTONDOWN && escapeOpen == false)
                            {switch(e.button.button)
                        /* If you use the mouse while the escape menu is closed put it here */
                                {
                                    case SDL_BUTTON_LEFT: break;
                                }}
                        if(e.type == SDL_QUIT) {quit = true;}
                        gWindow.handleEvent(e);
                        if(escapeOpen) {for(int i = 0; i < TOTAL_BUTTONS; ++i)
                            {gButtons[i].handleEvent(&e);}}
                    }
                }
			}
		}
	} close(); return 0;
}
