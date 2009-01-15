#include "VideoSDL_Base.hpp"


// Protected
char** VideoSDL_Base::GetVideoModes()
{
	// Get SDL screen modes
	SDL_Rect **modes;
	modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);

	// Count screen modes
	int numModes=0;
	while(modes[numModes])
		numModes++;

	// Create array to store screen modes in char format
	char** videoModes = new char*[numModes+1];
	videoModes[numModes] = NULL;
	numModes--;

	// Store screen modes
	for(int i=0; modes[i]; i++)
	{
		videoModes[i] = new char[10];
		sprintf(videoModes[i], "%dx%d", modes[numModes-i]->w,
										modes[numModes-i]->h);
	};

	// Return array with screen modes in char format
	return videoModes;
}

int VideoSDL_Base::GetWidth()
{
	return screen_->w;
}

int VideoSDL_Base::GetHeight()
{
	return screen_->h;
}


// Public
SDL_Surface* VideoSDL_Base::GetScreen()
{
	return screen_;
}


VideoSDL_Base::VideoSDL_Base(): screen_(NULL){}

VideoSDL_Base::~VideoSDL_Base()
{
	SDL_FreeSurface(screen_);
}
