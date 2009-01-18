//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "GX_Font.hpp"

#include <string.h>
#include <stdio.h>

#include "compileConfiguration.h"
#include "error.h"

#include "Video.hpp"
#ifdef SUPPORT_VIDEO_SDL
	#include "GX_GraphicSDL.hpp"

	#ifdef __APPLE__
		#include "SDL_ttf/SDL_ttf.h"
	#else
		#include "SDL/SDL_ttf.h"
	#endif
#endif

#include "GX_Common.hpp"


//	Protected

void* GX_Font::font_ = NULL;

char* GX_Font::fontPath_ = new char[256];
char* GX_Font::fontName_ = new char[32];
int GX_Font::fontSize_ = 0;


//	Public

void* GX_Font::Load(char* fontPath, char* fontName, int fontSize)
// Check if the font to load is diferent to the previously loaded font
// and if so, delete the old one and load the new one
{
	if(!font_								// If there's no loaded font
		|| strncmp(fontPath_, fontPath, 256)// or font path are diferent
		|| strncmp(fontName_, fontName, 32)	// or font name are diferent
		|| fontSize_!=fontSize				// or font size are diferent
		)
	{
		// Load new font parameters
		strncpy(fontPath_, fontPath, 256);
		strncpy(fontName_, fontName, 256);
		fontSize_=fontSize;

		// Compose full font path
		char fullFontPath[256];
		sprintf(fullFontPath, "%s/%s", fontPath_, fontName);

		// Load new font
		int option = GetOptionMultiple(Video::libraries_, "video",
										"graphic_library");
		#ifdef SUPPORT_VIDEO_SDL
			if(option==0)
			{
				TTF_CloseFont((TTF_Font*)font_);
				font_ = TTF_OpenFont(fullFontPath, fontSize_);
				return font_;
			}
		#else
			option++;
		#endif

		FATAL("No graphic libraries defined in source code!!!");
	}

	// Return previously loaded font
	return font_;
}