#ifndef WidgetTextbox_hpp
#define WidgetTextbox_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class WidgetTextbox: public MenuElement
{
private:
	GX_Graphic* image_;

	char block_[32];
	char option_[32];
	unsigned char fontSize_;
	char default_[32];

	char value_[256];
	char* visibleValue_;
	int cursor_;

	void Blink();

	void Render();
	void Draw(int x, int y);

public:
	void ProcessActions();

	WidgetTextbox(char* block, char* option, unsigned char size,
				char* def);
	~WidgetTextbox();
};

#endif
