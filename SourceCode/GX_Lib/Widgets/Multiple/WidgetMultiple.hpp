//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetMultiple_hpp
#define WidgetMultiple_hpp

#include "MenuElement.hpp"

#include "Actions.hpp"


class WidgetMultiple: public MenuElement
{
private:
	GX_Graphic* left_;
	GX_Graphic* center_;
	GX_Graphic* right_;

	char** options_;

	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	WidgetMultiple(char* block, char* option, char* options[]);
	~WidgetMultiple();
};

#endif
