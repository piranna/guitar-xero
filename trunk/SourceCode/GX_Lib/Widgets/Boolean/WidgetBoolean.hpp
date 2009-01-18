//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetBoolean_hpp
#define WidgetBoolean_hpp

#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class WidgetBoolean: public MenuElement
{
private:
	GX_Graphic* image_;

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
