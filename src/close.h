/*/
 * * * * * * * * * * * * * * * * * * * *
 * Purpose: Unload things from memory  *
 * * * * * * * * * * * * * * * * * * * *
/*/

void close()
{
    gButtonSpriteSheetTexture.free();
    gFPSTexture.free();
    //gBackgroundSpriteSheetTexture.free();

	gPicTexture.free();

	SDL_DestroyRenderer(gRenderer);
	gWindow.free();

	Mix_FreeMusic(gMusic); gMusic = NULL;

	SDL_Quit(); IMG_Quit(); Mix_Quit(); TTF_Quit();
}
