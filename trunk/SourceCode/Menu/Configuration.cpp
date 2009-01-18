//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Configuration.hpp"

#include "TextMenuManager.hpp"

#include "StartingMenu.hpp"
#include "GameConfig.hpp"
#include "ControlConfig.hpp"
#include "VideoConfig.hpp"
#include "SoundConfig.hpp"

#include "MenuContainer.hpp"
#include "MenuSubmenu.hpp"


void Configuration::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	host_->Append(new MenuContainer("Game config", 30,
									new MenuSubmenu()));
	host_->Append(new MenuContainer("Control config", 30,
									new MenuSubmenu()));
	host_->Append(new MenuContainer("Video config", 30,
									new MenuSubmenu()));
	host_->Append(new MenuContainer("Sound config", 30,
									new MenuSubmenu()));

	host_->AppendBack();
}


void Configuration::ActionBack()
{
	host_->SetMenuData(new StartingMenu());
}

void Configuration::ActionExec(int index)
{
	switch(index)
	{
		case 0:
			host_->SetMenuData(new GameConfig());
			break;
		case 1:
			host_->SetMenuData(new ControlConfig());
			break;
		case 2:
			host_->SetMenuData(new VideoConfig());
			break;
		case 3:
			host_->SetMenuData(new SoundConfig());
			break;
		case 4:	// Back
			ActionBack();
	};
}


Configuration::Configuration():
	TextMenu(){}
