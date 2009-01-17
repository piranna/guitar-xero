#ifndef PauseWindow_hpp
#define PauseWindow_hpp

#include "WidgetWindow.hpp"

#include "WidgetMenu.hpp"

#include "Timer.hpp"
#include "PlaySong.hpp"


class PauseWindow: public WidgetWindow
{
private:
	WidgetMenu* menu_;

	void ProcessActions();

public:
	PauseWindow( PlaySong* playSong);
	~PauseWindow();
};

#endif
