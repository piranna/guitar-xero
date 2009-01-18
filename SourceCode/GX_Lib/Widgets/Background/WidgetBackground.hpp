//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetBackground_hpp
#define WidgetBackground_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"


class WidgetBackground: public Widget
{
private:
	GX_Graphic* image_;

	void Draw(int x, int y);

public:
	WidgetBackground(char* path);
	~WidgetBackground();
};

#endif
