#include "Widget.hpp"


//	WidgetFocusable
void WidgetFocusable::SetFocus(bool focused)
// Set focus to widget
// and render it if focus has changed
{
	if(focused_!=focused)
	{
		focused_=focused;
		Render();
	}
}

WidgetFocusable::WidgetFocusable():
	focused_(false)
{}


//	WidgetPositionable
void WidgetPositionable::SetPos(int x, int y)
// Set relative position of the widget
{
	x_ = x;
	y_ = y;
}

WidgetPositionable::WidgetPositionable():
	x_(0), y_(0)
{}