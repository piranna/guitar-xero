#ifndef AudioSDL_h
#define AudioSDL_h

#include "Audio.hpp"

#include "SDL/SDL.h"
#ifdef __APPLE__
	   #include "SDL_mixer/SDL_mixer.h"
#else
	 #include "SDL/SDL_mixer.h"
#endif


class AudioSDL: public Audio
{
private:
	Mix_Music* music_;
	Mix_Chunk* guitar_;

	static void MusicDone();
	static void StopFailure(int channel);

public:
	static void Init();

	void LoadSong(char* songPath);

	void LoadMusic(char* musicPath);
	void PlayMusic(int loops);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();

	void LoadGuitar(char* musicPath);
	void PlayGuitar();
	void StopGuitar();
	void PauseGuitar();
	void ResumeGuitar();
	void VolumeGuitar(float volume);

	void PlayFailure(char* musicPath);

	AudioSDL();
	~AudioSDL();
};

#endif
