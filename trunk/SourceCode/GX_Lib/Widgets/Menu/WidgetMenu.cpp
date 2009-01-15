#include "WidgetMenu.hpp"

#include "WidgetLabel.hpp"


// Private
void WidgetMenu::Draw(int x, int y)
{
	menuManager_->Draw(x+x_, y+y_);
}


// Public
void WidgetMenu::ProcessActions()
{
	menuManager_->ProcessActions();

	UpdateMenu();
}

void WidgetMenu::ActionBack()
{
	menuData_->ActionBack();
}

void WidgetMenu::ActionExec()
{
	menuData_->ActionExec(index_);
}

void WidgetMenu::ActionPrev()
{
	if(menuElements_->Length())
	{
		index_--;
		if(index_ < 0)
			index_ = menuElements_->Length()-1;

		menuData_->SetIndex(index_);
	};
}

void WidgetMenu::ActionNext()
{
	if(menuElements_->Length())
	{
		index_++;
		if(index_ >= menuElements_->Length())
			index_ = 0;

		menuData_->SetIndex(index_);
	};
}

void WidgetMenu::SetMenuManager(MenuManager* menuManager)
// Set a new menu manager
{
	menuManagerAux_ = menuManager;
	menuManagerAux_->SetHost(this);
}

void WidgetMenu::SetMenuData(MenuData* menuData)
// Set a new menu data
{
	menuDataAux_ = menuData;
	menuDataAux_->SetHost(this);
}

void WidgetMenu::UpdateMenu()
// Change menu manager and/or menu data if one of them have been setted
{
	if(menuManagerAux_)
	{
		delete(menuManager_);
		menuManager_ = menuManagerAux_;
		menuManagerAux_ = NULL;
	}

	if(menuDataAux_)
	{
		delete(menuData_);
		menuData_ = menuDataAux_;
		menuDataAux_ = NULL;

		index_=0;
		Reload();
	}
}

void WidgetMenu::Append(Widget* menuElement)
{
	menuElements_->Append(menuElement);
}

void WidgetMenu::AppendBack()
{
	menuElements_->Append(NULL);
	menuElements_->Append(new WidgetLabel("Back", 30));
}

ListEntry* WidgetMenu::GetMenuElements()
{
	return menuElements_->GetList();
}

ListData* WidgetMenu::Get(int index)
{
	return menuElements_->GetData(index);
}

int WidgetMenu::GetIndex()
{
	return index_;
}

int WidgetMenu::GetLength()
{
	return menuElements_->Length();
}

void WidgetMenu::Reload()
{
	menuElements_->Reset();
	menuData_->Render();
	menuData_->SetIndex(index_);
}

void WidgetMenu::Reset()
{
	menuElements_->Reset();
}


WidgetMenu::WidgetMenu(MenuManager* menuManager, MenuData* menuData):
	menuManager_(menuManager),
	menuManagerAux_(NULL),
	menuData_(menuData),
	menuDataAux_(NULL),
	menuElements_(new List()),
	index_(0)
{
	menuManager_->SetHost(this);
	menuData_->SetHost(this);

	menuData_->Render();
	menuData->SetIndex(index_);
}
