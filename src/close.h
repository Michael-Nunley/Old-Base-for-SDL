void close()
{
    gButtonSpriteSheetTexture.free();
    gBackgroundSpriteSheetTexture.free();

	gPicTexture.free();

	SDL_DestroyRenderer(gRenderer);
	gWindow.free();

	Mix_FreeMusic(gMusic); gMusic = NULL;

	SDL_Quit(); IMG_Quit(); Mix_Quit(); TTF_Quit();
}
