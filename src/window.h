class LWindow
{
	public:
		LWindow();
		bool init();
		SDL_Renderer* createRenderer();
		void handleEvent(SDL_Event& e);
		void free();

		//window
		int getWidth();
		int getHeight();

		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();

	private:
		SDL_Window* mWindow;

		//window
		int mWidth;
		int mHeight;

		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
};

const char* SCREEN_TITLE = "SDL_BASE";
const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 640;

LWindow gWindow;

SDL_Renderer* LWindow::createRenderer() {return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);}

LWindow::LWindow()
{
	mWindow =           NULL;
	mMouseFocus =       false;
	mKeyboardFocus =    false;
	mFullScreen =       false;
	mMinimized =        false;
	mWidth =            0;
	mHeight =           0;
}

void LWindow::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_WINDOWEVENT)
	{
		bool updateCaption = false;

		switch(e.window.event)
		{
			case SDL_WINDOWEVENT_SIZE_CHANGED:  mWidth = e.window.data1; mHeight = e.window.data2; SDL_RenderPresent(gRenderer); break; //Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_EXPOSED:       SDL_RenderPresent( gRenderer ); break; //Repaint on exposure
			case SDL_WINDOWEVENT_ENTER:         mMouseFocus = true; updateCaption = true; break; //Mouse entered window
			case SDL_WINDOWEVENT_LEAVE:         mMouseFocus = false; updateCaption = true; break; //Mouse left window
			case SDL_WINDOWEVENT_FOCUS_GAINED:  mKeyboardFocus = true; updateCaption = true; break; //Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:    mKeyboardFocus = false; updateCaption = true; break; //Window lost keyboard focus
			case SDL_WINDOWEVENT_MINIMIZED:     mMinimized = true; break; //Window minimized
			case SDL_WINDOWEVENT_MAXIMIZED:     mMinimized = false; break; //Window maxized
			case SDL_WINDOWEVENT_RESTORED:      mMinimized = false; break; //Window restored
		}

		//Update window caption with new data
		if(updateCaption)
		{
			std::stringstream caption;
			caption
                << SCREEN_TITLE
                << " - MouseFocus:"
                << ((mMouseFocus) ?"On":"Off")
                << " KeyboardFocus:"
                << ((mKeyboardFocus) ?"On":"Off");

			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
	else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F10) //Toggle full screen F11
	{
		if(mFullScreen)     {SDL_SetWindowFullscreen(mWindow, SDL_FALSE); mFullScreen = false;}
		else                {SDL_SetWindowFullscreen(mWindow, SDL_TRUE); mFullScreen = true; mMinimized = false;}
	}
}

void LWindow::free()
{
	if(mWindow != NULL)     {SDL_DestroyWindow(mWindow);}
	mMouseFocus =           false;
	mKeyboardFocus =        false;
	mWidth =                0;
	mHeight =               0;
}

bool LWindow::init()
{
	//Create window
	mWindow = SDL_CreateWindow(
                            SCREEN_TITLE,
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
                            );
	if(mWindow != NULL)
	{
		mMouseFocus =       true;
		mKeyboardFocus =    true;
		mWidth =            SCREEN_WIDTH;
		mHeight =           SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}

bool LWindow::hasMouseFocus()       {return mMouseFocus;}
bool LWindow::hasKeyboardFocus()    {return mKeyboardFocus;}
bool LWindow::isMinimized()         {return mMinimized;}

int LWindow::getWidth()             {return mWidth;}
int LWindow::getHeight()            {return mHeight;}
