//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetAnimatedBackground_hpp
#define WidgetAnimatedBackground_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"


class WidgetAnimatedBackground: public WidgetPositionable
{
private:
	GX_Graphic* image_;

	void Draw(int x, int y);

public:
	void SetImage(char* path);

	WidgetAnimatedBackground();
	WidgetAnimatedBackground(char* path);
	~WidgetAnimatedBackground();
};

#endif
