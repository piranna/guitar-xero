//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef TextMenu_hpp
#define TextMenu_hpp

#include "MenuData.hpp"


class TextMenu: public MenuData
{
private:
	int index_;
	void SetIndex(int index);

protected:
	TextMenu();
};

#endif
