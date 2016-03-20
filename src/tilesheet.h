#include "Grasslands_A.h"
class Tile
{
    public:
		Tile();

		void setPosition(int x, int y);
		void render();

		bool isAnimated;
		bool IsSheetA;


    private:
		SDL_Point mPosition; //Top left position
        enumTiles mCurrentSprite = DIRT_GRASS_CENTER; //Currently used global sprite


};

SDL_Rect gBackgroundSprite[BG_SPRITE_TOTAL];
LTexture gBackgroundSpriteSheetTexture;

Tile::Tile()
{
	mPosition.x =       0;
	mPosition.y =       0;
	isAnimated =        false;
	IsSheetA =          true;
}

void Tile::setPosition(int x, int y) {mPosition.x = x; mPosition.y = y;}
void Tile::render()
{
	//Show current button sprite
	gBackgroundSpriteSheetTexture.render(mPosition.x, mPosition.y, &gBackgroundSprite[mCurrentSprite]);
}
