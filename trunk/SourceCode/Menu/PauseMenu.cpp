//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "PauseMenu.hpp"

#include "Audio.hpp"

#include "DirMenuManager.hpp"
#include "TextMenuManager.hpp"

#include "SongSelector.hpp"
#include "VolumeSettings.hpp"
#include "StartingMenu.hpp"

#include "MainLoop.hpp"
#include "MainMenu.hpp"

#include "ParserOptions.hpp"

#include "MenuContainer.hpp"
#include "WidgetLabel.hpp"
#include "MenuSubmenu.hpp"


void PauseMenu::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	host_->Append(new WidgetLabel("Continue", 48));

	host_->Append(NULL);

	host_->Append(new WidgetLabel("Reset song", 48));
		// [TO-DO] Remove option when playing tutorial
	host_->Append(new WidgetLabel("Change song", 48));
	host_->Append(new MenuContainer("Volumen settings", 48,
									new MenuSubmenu()));

	host_->Append(NULL);

	host_->Append(new WidgetLabel("Exit to home menu", 48));
}


void PauseMenu::ActionBack()
{
	playSong_->ClosePauseWindow();
}

void PauseMenu::ActionExec(int index)
{
	Actions::actions_->SetAction(MORE, false);
	Actions::actions_->SetAction(SELECT, false);

	switch(index)
	{
		case 0:		// Continue
			ActionBack();
			break;

		case 1:		// Reset song
			playSong_->ResetSong();
			ActionBack();
			break;

		case 2:		// Change song
			{
				ParserOptions parser(GUITARXERO_INI);
				parser.Read();

				char aux[256];
				strlcpy(aux, playSong_->GetSong()->GetSongPath(), 256);

				// Get dir path
				char* auxText = aux;
				char* auxIndex = aux;
				while(*auxText)
				{
					if(*auxText=='/')
						auxIndex=auxText;
					auxText++;
				}
				*auxIndex='\0';

				MainLoop::mainLoop_->SetWindow(
									new MainMenu(new DirMenuManager(),
												new SongSelector(aux)));
			}
			break;

		case 3:		// Volumen settings
			host_->SetMenuData(new VolumeSettings(playSong_));
			break;

		case 4:		// Exit to home menu
			MainLoop::mainLoop_->SetWindow(new MainMenu(new TextMenuManager(),
														new StartingMenu()));
	}
}


PauseMenu::PauseMenu(PlaySong* playSong):
	TextMenu(),
	playSong_(playSong){}
