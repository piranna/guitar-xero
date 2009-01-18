//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef MenuManager_hpp
#define MenuManager_hpp

#include "Widget.hpp"

#include "WidgetMenu.hpp"
class WidgetMenu;


class MenuManager: public Widget
{
protected:
	WidgetMenu* host_;

public:
	void SetHost(WidgetMenu* host);
};

class MenuManagerVertical: public MenuManager
{
private:
	void ProcessActions();
};

class MenuManagerHorizontal: public MenuManager
{
private:
	void ProcessActions();
};

#endif
