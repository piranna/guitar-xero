//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef __Timer_hpp__
#define __Timer_hpp__

#include <sys/time.h>

class Timer
{
private:
	double globalTime_;
	double diffTime_;
	double songTime_;

	double pausedTime_;

public:
	static Timer* timer_;

	void UpdateTime();

	double GetGlobalTime();
	double GetDiffTime();
	double GetSongTime();

	void InitSongTime(float delay);
	void PauseSong();
	void ResumeSong();
	bool IsSongPaused();

	Timer();
};

#endif
