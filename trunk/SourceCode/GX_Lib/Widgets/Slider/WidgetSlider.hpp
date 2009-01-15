#ifndef WidgetSlider_hpp
#define WidgetSlider_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"
#include "Actions.hpp"


class WidgetSlider: public MenuElement
{
private:
	GX_Graphic* image_;


	char block_[32];
	char option_[32];
	char default_[32];

	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	WidgetSlider(char* block, char* option, char* def);
	~WidgetSlider();
};

#endif
