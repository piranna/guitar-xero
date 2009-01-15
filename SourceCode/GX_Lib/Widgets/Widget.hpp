#ifndef Widget_hpp
#define Widget_hpp

#include "List.hpp"

#include <stdio.h>


class Widget: public ListData
{
public:
	virtual void Draw(int,int)=0;
	virtual void ProcessActions(){};
};


class WidgetFocusable: public Widget
{
protected:
	bool focused_;

	virtual void Render(){};

public:
	virtual void SetFocus(bool focused);

	WidgetFocusable();
};


class WidgetPositionable: public Widget
{
protected:
	int x_, y_;

public:
	void SetPos(int x, int y);

	WidgetPositionable();
};

#endif
