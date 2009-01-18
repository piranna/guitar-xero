//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Timer.hpp"

#include <stdlib.h>

#ifdef WIN32
// Dev-C++ does NOT have gettimeofday() function in <sys/time.h> :-(
// so, i have to "invent" it :-D

clock_t usOffset;

int	gettimeofday(struct timeval* tv, struct timezone * __restrict)
{
	tv->tv_sec = time(NULL);
	tv->tv_usec = long((((clock()-usOffset)%CLOCKS_PER_SEC)
						/float(CLOCKS_PER_SEC))*1000000);
//	[BUG] Esto va a tirones, ajustar microsegundos respecto a marca inicial
// Usar funcion residente en el archivo "sock_port.cpp", proyecto NetTest
}
#endif


Timer* Timer::timer_ = NULL;


void Timer::UpdateTime()
// Get current time and update all time counters
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double count = double(tv.tv_sec+tv.tv_usec/1000000.0);

	diffTime_ = count-globalTime_;
	globalTime_ = count;
}

double Timer::GetGlobalTime()
// Get time in seconds with fraction since epoch
{
	return globalTime_;
}

double Timer::GetDiffTime()
// Get diff time in seconds with fraction
{
	return diffTime_;
}

double Timer::GetSongTime()
// Get song time in seconds with fraction
{
	if(pausedTime_)
		return(pausedTime_-songTime_);

	return(globalTime_-songTime_);
}

void Timer::InitSongTime(float delay)
// Initialize song timer
// Delay set a diference from the actual time to init the timers
{
	songTime_ = globalTime_ - delay;
	pausedTime_ = 0;
}

void Timer::PauseSong()
// Set pausedTime_ to globalTime_ so it "apparently" from the programmer
// point of view all timers are stoped
{
	pausedTime_ = globalTime_;
}

void Timer::ResumeSong()
// If timers were stoped, reinit them
{
	if(pausedTime_)
	{
		songTime_ = songTime_ + (globalTime_ - pausedTime_);
		pausedTime_ = 0;
	};
}

bool Timer::IsSongPaused()
// Get if timers are paused
{
	return(pausedTime_);
}


Timer::Timer()
{
	if(!timer_)
	{
		timer_ = this;

		globalTime_=0;
		diffTime_=0;
		songTime_=0;
		pausedTime_=0;

		#ifdef WIN32
			long aux = time(NULL);
			do
			{
			} while(!(time(NULL) - aux));
			usOffset = clock();
	
//	[BUG] This is not the correct offset, adjust it in a second change.
		#endif
	}
}
