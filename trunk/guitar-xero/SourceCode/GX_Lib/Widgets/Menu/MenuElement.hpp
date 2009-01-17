#ifndef MenuElement_hpp
#define MenuElement_hpp

#include "Widget.hpp"

#include "MenuContainer.hpp"
class MenuContainer;


class MenuElement: public WidgetFocusable
{
protected:
	MenuContainer* host_;

public:
	void SetHost(MenuContainer* host){host_ = host;};

	MenuElement(): host_(NULL){};
};

#endif
