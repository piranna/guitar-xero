#ifndef MenuKey_hpp
#define MenuKey_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class MenuKey: public MenuElement
{
private:
	GX_Graphic* image_;

	char block_[32];
	char option_[32];
	char default_[32];

	void Blink();
	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	MenuKey(char* block, char* option, char* def);
	~MenuKey();
};

#endif
