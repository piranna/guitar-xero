//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef MenuData_hpp
#define MenuData_hpp


#include "WidgetMenu.hpp"
class WidgetMenu;


class MenuData
{
protected:
	WidgetMenu* host_;

public:
	void SetHost(WidgetMenu* host);
	virtual void Render()=0;

	virtual void ActionBack()=0;
	virtual void ActionExec(int)=0;

	virtual void SetIndex(int){};

	MenuData();
//	~MenuData();
};

#endif
