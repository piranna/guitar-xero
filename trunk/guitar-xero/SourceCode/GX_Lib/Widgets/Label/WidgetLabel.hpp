#ifndef WidgetLabel_hpp
#define WidgetLabel_hpp

#include "MenuEntry.hpp"

#include "GX_Graphic.hpp"


class WidgetLabel: public MenuEntry
{
private:
	virtual void Render();

protected:
	GX_Graphic* image_;
	char* text_;
	unsigned char size_;

	void SetText(char* text);

public:
	void Draw(int x, int y);

	int GetWidth();
	int GetHeight();

	WidgetLabel(char* text, unsigned char size);
	~WidgetLabel();
};

#endif
