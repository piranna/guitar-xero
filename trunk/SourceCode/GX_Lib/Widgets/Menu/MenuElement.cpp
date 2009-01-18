//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuElement.hpp"

#include <string.h>


void MenuElement::SetHost(MenuContainer* host)
{
	host_ = host;
}


MenuElement::MenuElement():
	host_(NULL), block_(NULL), option_(NULL)
{}

MenuElement::MenuElement(char* block, char* option):
	host_(NULL), block_(new char[32]), option_(new char[32])
{
	strlcpy(block_, block, 32);
	strlcpy(option_, option, 32);
}

MenuElement::~MenuElement()
{
	delete(block_);
	delete(option_);
}