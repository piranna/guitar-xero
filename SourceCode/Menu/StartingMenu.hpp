//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef StartingMenu_hpp
#define StartingMenu_hpp

#include "TextMenu.hpp"


class StartingMenu: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	StartingMenu();
};

#endif
