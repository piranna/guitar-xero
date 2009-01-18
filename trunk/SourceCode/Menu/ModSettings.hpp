//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef ModSettings_hpp
#define ModSettings_hpp

#include "TextMenu.hpp"


class ModSettings: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	ModSettings();
};

#endif
