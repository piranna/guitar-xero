//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetExactitude_hpp
#define WidgetExactitude_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"


class WidgetExactitude: public WidgetPositionable
{
private:
	void Render();

protected:
	GX_Graphic* star1_;
	GX_Graphic* star2_;

	float percent_;

	void Draw(int x, int y);

public:
	int GetWidth();
	int GetHeight();

	WidgetExactitude(float percent);
	~WidgetExactitude();
};

#endif
