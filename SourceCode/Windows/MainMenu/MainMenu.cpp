//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MainMenu.hpp"

#include "constants.hpp"

#include "WidgetBackground.hpp"
#include "common.hpp"


void MainMenu::ProcessActions()
{
	menu_->ProcessActions();
}

void MainMenu::SetAnimatedBackground(char* imagePath)
{
	if(imagePath)
		animatedBackground_->SetImage(imagePath);
}


MainMenu::MainMenu(MenuManager* menuManager, MenuData* menu):
	animatedBackground_(new WidgetAnimatedBackground()),
	menu_(new WidgetMenu(menuManager, menu))
{
	char path[256];
	GetFileExtension(path, MEDIA_DIR, "green-guitar-wallpaper");
	AppendWidget(new WidgetBackground(path));

	AppendWidget(animatedBackground_);

	GetFileExtension(path, MEDIA_DIR, "elvis_lapelvis");
//	AppendWidget(GX_Graphic::Make(path, 0,0));
//	AppendWidget(new WidgetAnimatedBackground(path));

	menu_->SetPos(50,50);
	AppendWidget(menu_);
}

MainMenu::~MainMenu()
{
	delete(animatedBackground_);
	delete(menu_);
}
