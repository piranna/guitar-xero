#include "TextMenu.hpp"

#include "Widget.hpp"


void TextMenu::SetIndex(int index)
{
	if(index != index_)
	{
		((WidgetFocusable*)host_->Get(index_))->SetFocus(false);
		index_ = index;
	}

	((WidgetFocusable*)host_->Get(index_))->SetFocus(true);
}


TextMenu::TextMenu():
	MenuData(),
	index_(0)
{}