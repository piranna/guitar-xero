#include "MenuContainer.hpp"


void MenuContainer::Draw(int x, int y)
{
	if(left_)
		left_->Draw(x, y);

	if(right_)
		right_->Draw(x + (left_->GetHeight()/2.0) + left_->GetWidth(), y);
}

int MenuContainer::GetHeight()
{
	return left_->GetHeight();
}

void MenuContainer::SetFocus(bool focused)
{
	left_->SetFocus(focused);
	right_->SetFocus(focused);
}

void MenuContainer::ProcessActions()
{
	right_->ProcessActions();
}


MenuContainer::MenuContainer(char* textLeft, unsigned char size,
							MenuElement* right):
	left_(new WidgetLabel(textLeft, size)), right_(right)
{
	right->SetHost(this);
}

MenuContainer::~MenuContainer()
{
	delete(left_);
	delete(right_);
}