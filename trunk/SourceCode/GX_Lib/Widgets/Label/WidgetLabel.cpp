//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetLabel.hpp"

#include "GX_Graphic.hpp"

#include <string.h>

#include "GX_common.hpp"
#include "constants.hpp"
#include "defaults.h"


void WidgetLabel::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}

void WidgetLabel::Render()
{
	if(image_)
		delete(image_);

	tColor color;
	if(focused_)
		color = Char2tColor(LoadTheme("base_color", BASE_COLOR));
	else
		color = Char2tColor(LoadTheme("selected_color", SELECTED_COLOR));

	image_ = GX_Graphic::Make(text_, MEDIA_DIR, "laundromat_1967.ttf", size_, color);
}

void WidgetLabel::SetText(char* text)
{
	if(text_)
	{
		if(strcmp(text_, text)!=0)
		{
			delete(text_);

			text_ = new char[32];
			strncpy(text_, text, 32);
			Render();
		}
	}
	else
	{
		text_ = new char[32];
		strncpy(text_, text, 32);
		Render();
	}
}

int WidgetLabel::GetWidth()
{
	return image_->GetWidth();
}

int WidgetLabel::GetHeight()
{
	return image_->GetHeight();
}


WidgetLabel::WidgetLabel(char* text, unsigned char size):
	image_(NULL), text_(NULL), size_(size)
{
	SetText(text);
}

WidgetLabel::~WidgetLabel()
{
	delete(image_);
}