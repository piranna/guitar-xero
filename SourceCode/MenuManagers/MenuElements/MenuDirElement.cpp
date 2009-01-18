//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuDirElement.hpp"

#include <string.h>

#include "common.hpp"


bool MenuDirElement::IsSong()
{
	return isSong_;
}

char* MenuDirElement::GetPath()
{
	return path_;
}

void MenuDirElement::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}


MenuDirElement::MenuDirElement(char* path, bool isSong):
	path_(NULL), isSong_(isSong), image_(NULL)
{
	if(path)
	{
		path_ = new char[256];
		strncpy(path_, path, 256);
	}
}

MenuDirElement::~MenuDirElement()
{
	delete(path_);
	delete(image_);
}
