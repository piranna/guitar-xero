#ifndef TryKeys_hpp
#define TryKeys_hpp

#include "WidgetWindow.hpp"

#include "Actions.hpp"
#include "Timer.hpp"
#include "WidgetKeynotes.hpp"


class TryKeys: public WidgetWindow
{
private:


	WidgetKeynotes* keyNotes_;

	void ProcessActions();

public:
	TryKeys();
};

#endif
