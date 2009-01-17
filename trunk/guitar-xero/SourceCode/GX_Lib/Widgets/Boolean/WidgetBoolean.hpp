#ifndef WidgetBoolean_hpp
#define WidgetBoolean_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class WidgetBoolean: public MenuElement
{
private:
	GX_Graphic* image_;

	char block_[32];
	char option_[32];
	bool enabled_;

	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	WidgetBoolean(char* block, char* option, bool enabled);
	WidgetBoolean(char* block, char* option);
	~WidgetBoolean();
};

#endif
