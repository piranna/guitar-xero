//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "StartingMenu.hpp"

#include <stdio.h>

#include "Audio.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "MainLoop.hpp"

#include "Song.hpp"

#include "DirMenuManager.hpp"
#include "SongSelector.hpp"
#include "PlaySong.hpp"
#include "SongEditor.hpp"
#include "Configuration.hpp"

#include "MenuContainer.hpp"
#include "WidgetLabel.hpp"
#include "MenuSubmenu.hpp"

#include <iostream>

void StartingMenu::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 48);

	host_->Append(new MenuContainer("Play", 48, new MenuSubmenu()));
	host_->Append(new WidgetLabel("Tutorial", 48));
	host_->Append(new MenuContainer("Song editor", 48, new MenuSubmenu()));
	host_->Append(new MenuContainer("Configuration", 48,
									new MenuSubmenu()));
	host_->Append(new WidgetLabel("Credits", 48));

	host_->Append(NULL);

	host_->Append(new WidgetLabel("Exit", 48));
}

void StartingMenu::ActionBack()
{
	exit(0);
}

void StartingMenu::ActionExec(int index)
{
	if(Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(LESS, false);
		ActionBack();
	}
	else
		switch(index)
		{
			case 0:		// Select Song
				{
					ParserOptions parser(GUITARXERO_INI);
					parser.Read();

					host_->SetMenuManager(new DirMenuManager());
					host_->SetMenuData(new SongSelector(
									parser.GetConfig("game", "songs_root",
													SONGS_ROOT)));
				};
				break;
			case 1:		// Tutorial
				{
					Song* song = new Song(TUTORIAL_PATH);

					ParserOptions parser(GUITARXERO_INI);
					parser.Read();
					song->ParseMidi(parser.GetConfig("player",
													"difficulty", "1"));

					MainLoop::mainLoop_->SetWindow(new PlaySong(song));
				}
				break;
			case 2:		// Song editor
				host_->SetMenuData(new SongEditor());
				break;
			case 3:		// Configuration
				host_->SetMenuData(new Configuration());
				break;
			case 4:		// Credits
				break;
			case 5:		// Exit
				ActionBack();
		}
}


StartingMenu::StartingMenu():
	TextMenu()
{
	char path[256];
	sprintf(path, "%s/%s", MEDIA_DIR, "menu.ogg");
	Audio::audio_->LoadMusic(path);
	Audio::audio_->PlayMusic(-1);
}