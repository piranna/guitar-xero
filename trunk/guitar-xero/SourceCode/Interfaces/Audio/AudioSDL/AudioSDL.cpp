#include "AudioSDL.hpp"

#include <stdlib.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "error.h"


void AudioSDL::MusicDone()
{
	audio_->StopMusic();
}


void AudioSDL::Init()
{
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
		FATAL("Unable to load SDL library (" << SDL_GetError() << ")");

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	Uint16 format;
	if(atoi(parser.GetConfig("audio", "bits"))==8)
		format=AUDIO_S8;
	else
		format=AUDIO_S16;

	int channels;
	if(strcmp(parser.GetConfig("audio", "stereo"), "True")==0)
		channels=2;
	else
		channels=1;

	if(Mix_OpenAudio(atoi(parser.GetConfig("audio", "frequency", "44100")),
					format, channels,
					atoi(parser.GetConfig("audio", "buffersize", "2048"))))
		FATAL("Error to init audio (" << SDL_GetError() << ")");
}


void AudioSDL::LoadSong(char* songPath)
{
	char path[256];

	sprintf(path, "%s/%s", songPath, "song.ogg");
	LoadMusic(path);

	sprintf(path, "%s/%s", songPath, "guitar.ogg");
	LoadGuitar(path);
}


// Music
void AudioSDL::LoadMusic(char* musicPath)
{
	StopMusic();	// stop and unload previusly loaded music, if any

	if(!(music_ = Mix_LoadMUS(musicPath)))
		ERROR("Error loading song (" << Mix_GetError() << ")");
}

void AudioSDL::PlayMusic(int loops)
{
	Mix_PlayMusic(music_, loops);
	Mix_HookMusicFinished(MusicDone);

	state_ = PLAYING;
}

void AudioSDL::StopMusic()
{
	if(music_)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music_);
		music_ = NULL;

		state_ = STOPPED;
	};
}

void AudioSDL::PauseMusic()
{
	Mix_PauseMusic();

	state_ = PAUSED;
}

void AudioSDL::ResumeMusic()
{
	Mix_ResumeMusic();

	state_ = PLAYING;
}


// Guitar
void AudioSDL::LoadGuitar(char* musicPath)
{
	StopGuitar();	// stop and unload previusly loaded guitar, if any

	if(!(guitar_ = Mix_LoadWAV(musicPath)))
		ERROR("Error loading guitar (" << Mix_GetError() << ")");
}

void AudioSDL::PlayGuitar()
{
	Mix_PlayChannel(-1, guitar_, 0);
}

void AudioSDL::StopGuitar()
{
	if(guitar_)
	{
		Mix_HaltChannel(-1);
		Mix_FreeChunk(guitar_);
		guitar_=NULL;
	};
}

void AudioSDL::PauseGuitar()
{
	Mix_Pause(-1);
}

void AudioSDL::ResumeGuitar()
{
	Mix_Resume(-1);
}

void AudioSDL::VolumeGuitar(float volume)
{
	Mix_VolumeChunk(guitar_, int(128*volume));
}


// Failure
void AudioSDL::PlayFailure(char* musicPath)
{
	Mix_Chunk* chunk = Mix_LoadWAV(musicPath);
	if(chunk)
	{
		Mix_PlayChannel(-1, chunk, 0);
		Mix_ChannelFinished(StopFailure);
	}
	else
		ERROR("Error loading " << musicPath << " (" << Mix_GetError()
				<< ")");
}

void AudioSDL::StopFailure(int channel)
{
	Mix_FreeChunk(Mix_GetChunk(channel));
}


// Constructor/Destructor
AudioSDL::AudioSDL():
	music_(NULL),
	guitar_(NULL)
{}

AudioSDL::~AudioSDL()
{
	StopMusic();
	StopGuitar();

	Mix_CloseAudio();
}
