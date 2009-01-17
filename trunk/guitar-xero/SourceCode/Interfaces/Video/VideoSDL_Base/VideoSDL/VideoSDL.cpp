#include "VideoSDL.hpp"

#ifdef __APPLE__
	#include "SDL_ttf/SDL_ttf.h"
	#include "SDL_gfxPrimitives.h"
#else
	#include "SDL/SDL_ttf.h"
	#include "SDL/SDL_gfxPrimitives.h"
#endif

#include "compileConfiguration.h"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "error.h"


// Private
bool VideoSDL::InitScreen()
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	// SDL_SWSURFACE, SDL_HWSURFACE, SDL_ASYNCBLIT, SDL_ANYFORMAT
	// SDL_HWPALETTE, SDL_DOUBLEBUF, SDL_FULLSCREEN, SDL_OPENGL
	// SDL_OPENGLBLIT, SDL_RESIZABLE

	Uint32 flags=(SDL_HWSURFACE | SDL_DOUBLEBUF);

#ifdef SUPPORT_VIDEO_WINDOWING	// Allow to force fullscreen on platforms
								// that doesn't support windowing
	if(!strncmp(parser.GetConfig("video", "fullscreen"), "True", 4))
#endif
		flags=(flags | SDL_FULLSCREEN);

	char resolution[10];
	char** videoModes = GetVideoModes();
	strcpy(resolution,
			parser.GetConfig("video", "resolution", videoModes[0]));

	// Delete video modes (prevent memory leaks)
	for(int i=0; videoModes[i]; i++)
		delete(videoModes[i]);
	delete(videoModes);

	int resX = atoi(strtok(resolution, "x"));
	int resY = atoi(strtok(NULL, "x"));

	SDL_Surface* aux = SDL_SetVideoMode(resX, resY, 32, flags);

	if(aux)
	{
		if(screen_)
			SDL_FreeSurface(screen_);
		screen_=aux;
	}
	else
	{
		ERROR("Unable to activate " << resX << "x" << resY
				<< "x32 video mode (" << SDL_GetError() << ")");
		return true;
	};

	return false;
}

bool VideoSDL::CanRender3D()
{
	return false;
}

void VideoSDL::Flip()
{
	SDL_Flip(screen_);
}

void VideoSDL::FilledCircle(int x, int y, int radius,
							unsigned char r,
							unsigned char g,
							unsigned char b,
							unsigned char a)
{
	filledCircleRGBA(screen_, x, y, radius, r, g, b, a);
}


// Public
void VideoSDL::Init()
{
	// video
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		FATAL("Unable to load SDL library (" << SDL_GetError() << ")");

	// fonts
	if(TTF_Init() < 0)
		FATAL("Unable to initialize SDL_ttf (" << TTF_GetError() << ")");

	// Prepair SDL ending
	atexit(SDL_Quit);
	atexit(TTF_Quit);
}


VideoSDL::VideoSDL()
{
	if(InitScreen())	// if fails initialization of screen...
		exit(1);		// ...close the app
}
