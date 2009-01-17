#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "WidgetWindow.hpp"

#include "WidgetAnimatedBackground.hpp"
#include "WidgetMenu.hpp"

#include "MenuManager.hpp"
#include "MenuData.hpp"


class MainMenu: public WidgetWindow
{
private:
	WidgetAnimatedBackground* animatedBackground_;
	WidgetMenu* menu_;

	void ProcessActions();

public:
	void SetAnimatedBackground(char* imagePath);

	MainMenu(MenuManager* menuManager, MenuData* menu);
	~MainMenu();
};

#endif
