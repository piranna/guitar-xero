//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetSlider_hpp
#define WidgetSlider_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"
#include "Actions.hpp"


class WidgetSlider: public MenuElement
{
private:
	GX_Graphic* image_;

	char default_[32];

	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	WidgetSlider(char* block, char* option, char* def);
	~WidgetSlider();
};

#endif
