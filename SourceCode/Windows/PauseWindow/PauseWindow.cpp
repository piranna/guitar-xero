#include "PauseWindow.hpp"

#include "PauseMenu.hpp"

#include "TextMenuManager.hpp"


void PauseWindow::ProcessActions()
{
	menu_->ProcessActions();
}


PauseWindow::PauseWindow(PlaySong* playSong):
	menu_(new WidgetMenu(new TextMenuManager(), new PauseMenu(playSong)))
{
	menu_->SetPos(50,50);
	AppendWidget(menu_);
}

PauseWindow::~PauseWindow()
{
	delete(menu_);
}
