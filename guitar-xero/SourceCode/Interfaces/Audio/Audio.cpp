#include "Audio.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "compileConfiguration.h"
#include "error.h"

#ifdef SUPPORT_AUDIO_SDL
	#include "AudioSDL.hpp"
#endif

#include "GX_common.hpp"


Audio* Audio::audio_ = NULL;

tState Audio::state_ = STOPPED;

char* Audio::libraries_[] =
{
	#ifdef SUPPORT_AUDIO_SDL
		"SDL",
	#endif
	NULL
};

char* Audio::frequencies_[] =
{
	"11025",
	"22050",
	"44100",
	NULL
};

char* Audio::bits_[] =
{
	"8",
	"16",
	NULL
};

char* Audio::bufferSizes_[] =
{
	"1024",
	"2048",
	"3072",
	"4096",
	NULL
};


tState Audio::GetState()
{
	return state_;
}


void Audio::Select()
{
	if(audio_)
		delete(audio_);

	int option = GetOptionMultiple(libraries_, "audio", "audio_library");

	#ifdef SUPPORT_AUDIO_SDL
		if(option==0)
		{
			AudioSDL::Init();
			audio_ = new AudioSDL();
			return;
		};
	#endif

	FATAL("No audio libraries defined in source code!!!");
}