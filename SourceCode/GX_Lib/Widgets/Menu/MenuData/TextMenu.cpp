//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "TextMenu.hpp"

#include "Widget.hpp"


void TextMenu::SetIndex(int index)
{
	// If new index different from local index,
	// set element focus to false and update local index
	if(index != index_)
	{
		((WidgetFocusable*)host_->Get(index_))->SetFocus(false);
		index_ = index;
	}

	// Set new focused element to true.
	// This is done always because elements are not-focused by default
	((WidgetFocusable*)host_->Get(index_))->SetFocus(true);
}


TextMenu::TextMenu():
	MenuData(),
	index_(0)
{}