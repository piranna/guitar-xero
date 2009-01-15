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
