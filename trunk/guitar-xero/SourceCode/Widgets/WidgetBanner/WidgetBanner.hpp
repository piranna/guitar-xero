#ifndef WidgetBanner_hpp
#define WidgetBanner_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"


class WidgetBanner: public WidgetPositionable
{
private:
	void Render();

protected:
	GX_Graphic* image_;
	char* text_;
	unsigned char size_;

	void SetText(char* text);

public:
	void Draw(int x, int y);

	int GetWidth();
	int GetHeight();

	WidgetBanner(char* text, unsigned char size);
	~WidgetBanner();
};

#endif
