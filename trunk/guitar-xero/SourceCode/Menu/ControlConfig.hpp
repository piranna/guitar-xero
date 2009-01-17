#ifndef ControlConfig_hpp
#define ControlConfig_hpp

#include "TextMenu.hpp"


class ControlConfig: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	ControlConfig();
};

#endif
