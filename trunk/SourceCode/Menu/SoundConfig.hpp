#ifndef SoundConfig_hpp
#define SoundConfig_hpp

#include "TextMenu.hpp"


class SoundConfig: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	SoundConfig();
};

#endif
