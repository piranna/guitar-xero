//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef MenuElement_hpp
#define MenuElement_hpp

#include "Widget.hpp"

#include "MenuContainer.hpp"
class MenuContainer;


class MenuElement: public WidgetFocusable
{
protected:
	MenuContainer* host_;

	char* block_;
	char* option_;

public:
	void SetHost(MenuContainer* host);

	MenuElement();
	MenuElement(char* block, char* option);
	~MenuElement();
};

#endif
