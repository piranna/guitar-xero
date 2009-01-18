//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetTextbox_hpp
#define WidgetTextbox_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class WidgetTextbox: public MenuElement
{
private:
	GX_Graphic* image_;

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
