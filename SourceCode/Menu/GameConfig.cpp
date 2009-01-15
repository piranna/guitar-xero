#include "GameConfig.hpp"

#include <dirent.h>

#include "ParserOptions.hpp"
#include "constants.hpp"
#include "defaults.h"

#include "Configuration.hpp"
#include "ModSettings.hpp"

#include "Input.hpp"

#include "MenuContainer.hpp"
#include "MenuSubmenu.hpp"
#include "WidgetBoolean.hpp"
#include "WidgetMultiple.hpp"
#include "WidgetTextbox.hpp"


char** GameConfig::GetLanguages()
{
	char** options = new char*[100];	// arbitrary number of languages

	// Add default option
	options[0] = new char[32];
	strcpy(options[0], "English");
	int maxOptions = 1;

	// Load language dir
	DIR* pdir = opendir(LANGUAGES_PATH);
	struct dirent* pent;

	// Get dir entries
	while(pent=readdir(pdir))	// elements in directory
		if((strcmp((char*)pent->d_name, ".")!= 0)
			&& (strcmp((char*)pent->d_name, "..")!= 0))
		{
			options[maxOptions] = new char[32];
			strcpy(options[maxOptions], (char*)pent->d_name);
			Untail(options[maxOptions], 5);
			maxOptions++;
		};
	closedir(pdir);

	options[maxOptions] = NULL;

	return options;
}

void GameConfig::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new MenuContainer("Mod settings", 30, new MenuSubmenu()));
	host_->Append(new MenuContainer("Language", 30,
							new WidgetMultiple("game", "language",
												languages_)));
	host_->Append(new MenuContainer("Songs root", 30,
							new WidgetTextbox("game", "songs_root", 30,
												SONGS_ROOT)));
	host_->Append(new MenuContainer("Left mode", 30,
							new WidgetBoolean("game", "leftymode")));
	host_->Append(new MenuContainer("Tappable notes", 30,
							new WidgetBoolean("game", "tapping")));
	host_->Append(new MenuContainer("Upload punctuations", 30,
							new WidgetBoolean("game", "uploadscores")));
	host_->Append(new MenuContainer("Subtitles", 30,
							new WidgetBoolean("game", "subtitles")));

	host_->AppendBack();
}

void GameConfig::ActionBack()
{
	host_->SetMenuData(new Configuration());
}

void GameConfig::ActionExec(int index)
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	switch(index)
	{
		case 0:
			if(Actions::actions_->GetAction(MORE) ||
				Actions::actions_->GetAction(SELECT))
			{
				host_->SetMenuData(new ModSettings());
			};
			break;
		case 1:		// Language
			((MenuContainer*)host_->Get(index))->ProcessActions();

			host_->Reload();
			break;
		case 2:		// Songs Root
			((MenuContainer*)host_->Get(index))->ProcessActions();
			break;
		case 3: case 4: case 5: case 6:
			((MenuContainer*)host_->Get(index))->ProcessActions();

			Actions::actions_->SetAction(SELECT, false);
			Actions::actions_->SetAction(MORE, false);
			Actions::actions_->SetAction(LESS, false);
			break;

		default:	// Back
			ActionBack();
	}
}


GameConfig::GameConfig():
	TextMenu(), languages_(GetLanguages())
{}

GameConfig::~GameConfig()
{
	for(int i=0; languages_[i]; i++)
		delete(languages_[i]);
	delete(languages_);
}