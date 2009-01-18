//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuSubmenu.hpp"

#include "constants.hpp"
#include "defaults.h"


void MenuSubmenu::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}

void MenuSubmenu::SetFocus(bool focused)
{
	if(image_)
		delete(image_);

	if(focused)
	{
		char path[256];
		sprintf(path, "%s/%s", MEDIA_DIR, "right.png");
		image_ = GX_Graphic::Make(path, 0, host_->GetHeight());
	}
	else
		image_ = NULL;
}


MenuSubmenu::MenuSubmenu():
	image_(NULL)
{}

MenuSubmenu::~MenuSubmenu()
{
	delete(image_);
}