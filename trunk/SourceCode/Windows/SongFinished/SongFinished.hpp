//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef SongFinished_hpp
#define SongFinished_hpp

#include "WidgetWindow.hpp"

#include "Actions.hpp"
#include "Timer.hpp"

class SongFinished: public WidgetWindow
{
private:


	void ProcessActions();

public:
	SongFinished(
				int puntuation, float percent, int maxHits);
};

#endif
