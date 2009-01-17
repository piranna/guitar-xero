#ifndef NoSongs_hpp
#define NoSongs_hpp

#include "TextMenu.hpp"


class NoSongs: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	NoSongs();
};

#endif
