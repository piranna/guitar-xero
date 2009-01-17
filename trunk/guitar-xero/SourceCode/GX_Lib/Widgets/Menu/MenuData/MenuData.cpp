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
