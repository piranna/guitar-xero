#ifndef WidgetWindow_hpp
#define WidgetWindow_hpp

#include "Widget.hpp"

#include "List.hpp"


class WidgetWindow: public WidgetPositionable
{
private:
	List* widgets_;

protected:
	WidgetWindow();

public:
	void AppendWidget(Widget* widget);
	void RemoveLastWidget();

	void Draw(int x, int y);

	~WidgetWindow();
};

#endif
