//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef VideoSDL_Base_hpp
#define VideoSDL_Base_hpp

#include "Video.hpp"

#include "SDL/SDL.h"


class VideoSDL_Base: public Video
{
protected:
	SDL_Surface* screen_;

	char** GetVideoModes();

	int GetWidth();
	int GetHeight();

	VideoSDL_Base();
	~VideoSDL_Base();

public:
	SDL_Surface* GetScreen();
};

#endif
