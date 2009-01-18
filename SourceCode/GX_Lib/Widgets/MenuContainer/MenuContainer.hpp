//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef MenuContainer_hpp
#define MenuContainer_hpp

#include "MenuEntry.hpp"

#include "WidgetLabel.hpp"
#include "MenuElement.hpp"
class MenuElement;


class MenuContainer: public MenuEntry
{
private:
	WidgetLabel* left_;
	MenuElement* right_;

	void Draw(int x, int y);
	void SetFocus(bool focused);

public:
	void ProcessActions();

	int GetHeight();

	MenuContainer(char* textLeft, unsigned char size, MenuElement* right);
	~MenuContainer();
};

#endif
