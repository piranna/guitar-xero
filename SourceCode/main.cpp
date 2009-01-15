#include "compileConfiguration.h"

#include "Timer.hpp"
#include "Actions.hpp"

#include "Input.hpp"
#include "Video.hpp"
#include "Audio.hpp"

#include "MainLoop.hpp"
#include "MainMenu.hpp"

#include "TextMenuManager.hpp"
#include "StartingMenu.hpp"


// This is needed because XCode SDL needs to add a little
// pre-compilation code in main function
#ifdef SUPPORT_VIDEO_SDL | \
		SUPPORT_VIDEO_OpenGL_SDL | \
		SUPPORT_INPUT_SDL | \
		SUPPORT_AUDIO_SDL
	#include "SDL/SDL.h"
#endif


#ifdef _XBOX
	void XBoxStartup()
#else
	int main(int arg, char** argv)
#endif
{
	// Init basics
	Timer timer;
	Actions actions;

	// Init interfaces
	Input::Select(&actions);
	Video::Select();
	Audio::Select();

	// Start game
	MainLoop(new MainMenu(new TextMenuManager(), new StartingMenu()));

	return(0);
}
