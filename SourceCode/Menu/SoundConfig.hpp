//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


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
