//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef Audio_hpp
#define Audio_hpp


typedef enum{PLAYING, PAUSED, STOPPED} tState;

class Audio
{
protected:
	static tState state_;

public:
	static Audio* audio_;
	static char* libraries_[];
	static char* frequencies_[];
	static char* bits_[];
	static char* bufferSizes_[];
	static void Select();
	static tState GetState();

//	virtual void MusicDone()=0;

	virtual void LoadMusic(char*)=0;

	virtual void LoadSong(char*)=0;

	virtual void PlayMusic(int)=0;
	virtual void StopMusic()=0;
	virtual void PauseMusic()=0;
	virtual void ResumeMusic()=0;

	virtual void PlayGuitar()=0;
	virtual void StopGuitar()=0;
	virtual void PauseGuitar()=0;
	virtual void ResumeGuitar()=0;
	virtual void VolumeGuitar(float)=0;

	virtual void PlayFailure(char*)=0;
};

#endif
