enum LButtonSprite
{
	BACK_BUTTON_SPRITE_MOUSE_OUT = 0,
	BACK_BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	QUIT_BUTTON_SPRITE_MOUSE_OUT = 2,
	QUIT_BUTTON_SPRITE_MOUSE_OVER_MOTION = 3,

	BUTTON_SPRITE_TOTAL = 4
};

class LButton
{
	public:
		LButton();

		void setPosition(int x, int y);
		void handleEvent(SDL_Event *e);//Handles mouse event
		void render();
		bool isExitButton;

	private:
		SDL_Point mPosition; //Top left position
		LButtonSprite mCurrentSprite; //Currently used global sprite
};

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

const int BUTTON_WIDTH =        300;
const int BUTTON_HEIGHT =       200;

LButton::LButton()
{
	mPosition.x =       0;
	mPosition.y =       0;

	if (isExitButton)
    {
        mCurrentSprite =    QUIT_BUTTON_SPRITE_MOUSE_OUT;
    }
    else
    {
        mCurrentSprite =    BACK_BUTTON_SPRITE_MOUSE_OUT;
    }
}

void LButton::setPosition(int x, int y) {mPosition.x = x; mPosition.y = y;}
void LButton::handleEvent(SDL_Event *e)
{
    if (isExitButton) {mCurrentSprite = QUIT_BUTTON_SPRITE_MOUSE_OUT;}

	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) //If mouse event happened
	{
        int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if(x < mPosition.x)                         {inside = false;}
		else if(x > mPosition.x + BUTTON_WIDTH)     {inside = false;}
		else if(y < mPosition.y)                    {inside = false;}
		else if(y > mPosition.y + BUTTON_HEIGHT)    {inside = false;}


		if (isExitButton)
        {
            if(!inside) {mCurrentSprite = QUIT_BUTTON_SPRITE_MOUSE_OUT;} //Mouse is outside button
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                switch(e->type)
                {
                    case SDL_MOUSEMOTION:
                        mCurrentSprite = QUIT_BUTTON_SPRITE_MOUSE_OVER_MOTION;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        break;
                }
                if (e->type == SDL_MOUSEBUTTONDOWN)
                {
                    switch(e->button.button)
                    {
                        case SDL_BUTTON_LEFT: quit = true; break;
                    }
                }
            }
        }
        else
        {
            if(!inside) {mCurrentSprite = BACK_BUTTON_SPRITE_MOUSE_OUT;} //Mouse is outside button
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                switch(e->type)
                {
                    case SDL_MOUSEMOTION:
                        mCurrentSprite = BACK_BUTTON_SPRITE_MOUSE_OVER_MOTION;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        break;
                }
                if (e->type == SDL_MOUSEBUTTONDOWN)
                {
                    switch(e->button.button)
                    {
                        case SDL_BUTTON_LEFT: escapeOpen = false; break;
                    }
                }
            }
        }
	}
}

void LButton::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
