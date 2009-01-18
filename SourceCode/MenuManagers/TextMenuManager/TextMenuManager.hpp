//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef TextMenuManager_hpp
#define TextMenuManager_hpp

#include "MenuManager.hpp"


class TextMenuManager: public MenuManagerVertical
{
private:
	void Draw(int x, int y);

public:
	TextMenuManager();
};

#endif
