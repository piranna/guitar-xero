//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


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
