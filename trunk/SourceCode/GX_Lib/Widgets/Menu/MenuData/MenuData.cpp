//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuData.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"


void MenuData::SetHost(WidgetMenu* host)
{
	host_ = host;
}


MenuData::MenuData():
	host_(NULL)
{}
