//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetBanner.hpp"

#include "GX_Graphic.hpp"

#include <string.h>

#include "GX_common.hpp"

#include "constants.hpp"
#include "defaults.h"


void WidgetBanner::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x_+x, y_+y);
}

void WidgetBanner::Render()
{
	if(image_)
		delete(image_);

	if(text_)
		image_ = GX_Graphic::Make(text_, MEDIA_DIR, "laundromat_1967.ttf", size_,
						Char2tColor(LoadTheme("base_color", BASE_COLOR)));
	else
		image_ = NULL;
}

void WidgetBanner::SetText(char* text)
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

int WidgetBanner::GetWidth()
{
	return image_->GetWidth();
}

int WidgetBanner::GetHeight()
{
	return image_->GetHeight();
}


WidgetBanner::WidgetBanner(char* text, unsigned char size):
	image_(NULL), text_(NULL), size_(size)
{
	SetText(text);
}

WidgetBanner::~WidgetBanner()
{
	delete(image_);
}