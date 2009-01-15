#include "GX_Graphic.hpp"

#include "compileConfiguration.h"
#include "error.h"

#include "Video.hpp"

#ifdef SUPPORT_VIDEO_SDL
	#include "GX_GraphicSDL.hpp"
#endif

#include "GX_Common.hpp"


//	Empty Image
GX_Graphic* GX_Graphic::Make(int w, int h)
// Make an empty graphic of w and h sizes
{
	int option = GetOptionMultiple(Video::libraries_, "video",
									"graphic_library");

	#ifdef SUPPORT_VIDEO_SDL
		if(option==0)
			return new GX_GraphicSDL(w, h);
	#else
		option++;
	#endif

	FATAL("No graphic libraries defined in source code!!!");
}


//	Image
GX_Graphic* GX_Graphic::Make(char* path, int w, int h)
// Make a graphic with a image defined in 'path'
// and adjust it's size to w and h if they are diferent from NULL
{
	int option = GetOptionMultiple(Video::libraries_, "video",
									"graphic_library");

	#ifdef SUPPORT_VIDEO_SDL
		if(option==0)
			return new GX_GraphicSDL(path, w, h);
	#else
		option++;
	#endif

	FATAL("No graphic libraries defined in source code!!!");
}


//	Text
GX_Graphic* GX_Graphic::Make(char* text, char* fontPath, char size,
							tColor color)
// Make a graphic with a rendered text inside
{
	int option = GetOptionMultiple(Video::libraries_, "video",
									"graphic_library");

	#ifdef SUPPORT_VIDEO_SDL
		if(option==0)
			return new GX_GraphicSDL(text, fontPath, size, color);
	#else
		option++;
	#endif

	FATAL("No graphic libraries defined in source code!!!");
}