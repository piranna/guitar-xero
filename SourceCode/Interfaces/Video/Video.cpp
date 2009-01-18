//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Video.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "compileConfiguration.h"
#include "error.h"

#ifdef SUPPORT_VIDEO_SDL
	#include "VideoSDL.hpp"
#endif
#ifdef SUPPORT_VIDEO_OpenGL_SDL
//	#include "VideoOGL_SDL_2D.hpp"
#endif

#include "GX_common.hpp"


Video* Video::video_ = NULL;

char* Video::libraries_[] =
{
	#ifdef SUPPORT_VIDEO_SDL
		"SDL",
	#endif
	#ifdef SUPPORT_VIDEO_OpenGL_SDL
		"OpenGL",
	#endif
	NULL
};


void Video::Select()
{
	if(video_)
		delete(video_);

	int option = GetOptionMultiple(libraries_, "video", "graphic_library");

	#ifdef SUPPORT_VIDEO_SDL
		if(option==0)
		{
			VideoSDL::Init();
			video_ = new VideoSDL();
			return;
		};
	#else
		option++;
	#endif

	#ifdef SUPPORT_VIDEO_OpenGL_SDL
		if(option==1)
		{
//			VideoOGL_SDL_2D::Init();
//			video = new VideoOGL_SDL_2D();
//			return;
		};
	#else
		option++;
	#endif

	FATAL("No video libraries defined in source code!!!");
}
