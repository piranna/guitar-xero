//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetSplash_hpp
#define WidgetSplash_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"


class WidgetSplash: public Widget
{
private:
	GX_Graphic* image_;
	double splashTime_;

public:
	void Draw(int x, int y);

	double GetTime();

	WidgetSplash(GX_Graphic* image);
	~WidgetSplash();
};

#endif
