//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "ModSettings.hpp"

#include <dirent.h>
#include <stdio.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "GameConfig.hpp"

#include "MenuContainer.hpp"
#include "WidgetBoolean.hpp"


void ModSettings::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	DIR* pdir = opendir(MODS_PATH);
	struct dirent* pent;

	while(pent=readdir(pdir))	// elements in directory
		if((strcmp((char*)pent->d_name, ".")!= 0)
			&& (strcmp((char*)pent->d_name, "..")!= 0))
		{
			char listEntry[32];
			sprintf(listEntry, "mod_%s", (char*)pent->d_name);

			host_->Append(new MenuContainer((char*)pent->d_name, 30,
								new WidgetBoolean("mods", listEntry)));
		};
	closedir(pdir);

	host_->AppendBack();
}

void ModSettings::ActionBack()
{
	host_->SetMenuData(new GameConfig());
}

void ModSettings::ActionExec(int index)
{
	if(index==host_->GetLength()-1)
	{
//		video->SetAnimator(new FadeOut(-300000, 60));
		ActionBack();
	}

	else
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();

		host_->Reload();	// [TO-DO] Reload all screen, not only menu
	}
}


ModSettings::ModSettings():
	TextMenu()
{}
