//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetBackground.hpp"

#include "GX_Graphic.hpp"


void WidgetBackground::Draw(int x, int y)
// Draw background
{
	image_->Draw(x,y);
}

WidgetBackground::WidgetBackground(char* path):
	image_(GX_Graphic::Make(path, 0,0)){}


WidgetBackground::~WidgetBackground()
{
	delete(image_);
}
