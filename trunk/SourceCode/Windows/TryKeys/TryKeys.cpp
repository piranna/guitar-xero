//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "TryKeys.hpp"

#include "common.hpp"
#include "constants.hpp"

#include "MainLoop.hpp"

#include "MainMenu.hpp"
#include "TextMenuManager.hpp"
#include "ControlConfig.hpp"

#include "WidgetBackground.hpp"
#include "WidgetLabel.hpp"
#include "WidgetBanner.hpp"

#include "Video.hpp"


void TryKeys::ProcessActions()
{
	if(Actions::actions_->GetAction(BACK))
	{
		Actions::actions_->SetAction(BACK, false);
		MainLoop::mainLoop_->SetWindow(new MainMenu(new TextMenuManager(),
													new ControlConfig()));
	}

	else
		keyNotes_->ProcessActions();
}


TryKeys::TryKeys():
	keyNotes_(new WidgetKeynotes())
{
	char path[256];
	GetFileExtension(path, MEDIA_DIR, "green-guitar-wallpaper");
	AppendWidget(new WidgetBackground(path));

	WidgetBanner* banner = new WidgetBanner("Play with the keys", 48);
	banner->SetPos((Video::video_->GetWidth() - banner->GetWidth())/2.0,
					30);
	AppendWidget(banner);

	keyNotes_->SetPos((Video::video_->GetWidth() - banner->GetWidth())/2.0,
					200);
	AppendWidget(keyNotes_);
}