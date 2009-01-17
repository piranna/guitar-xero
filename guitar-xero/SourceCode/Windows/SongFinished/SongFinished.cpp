#include "SongFinished.hpp"

#include "common.hpp"
#include "constants.hpp"

#include "MainLoop.hpp"

#include "TextMenuManager.hpp"
#include "MainMenu.hpp"
#include "StartingMenu.hpp"

#include "WidgetBanner.hpp"
#include "WidgetBackground.hpp"
#include "WidgetExactitude.hpp"

#include "Video.hpp"


void SongFinished::ProcessActions()
{
	if(Actions::actions_->GetAction(SELECT))
		MainLoop::mainLoop_->SetWindow(new MainMenu(new TextMenuManager(),
													new StartingMenu()));
}


SongFinished::SongFinished(int puntuation, float percent, int maxHits)
{
	char aux[256];
	GetFileExtension(aux, MEDIA_DIR, "green-guitar-wallpaper");
	AppendWidget(new WidgetBackground(aux));

	WidgetBanner* info = new WidgetBanner("Song finished!", 48);
	info->SetPos((Video::video_->GetWidth()-info->GetWidth())/2.0, 50);
	AppendWidget(info);

	sprintf(aux, "%i", puntuation);
	info = new WidgetBanner(aux, 120);
	info->SetPos((Video::video_->GetWidth()-info->GetWidth())/2.0, 100);
	AppendWidget(info);

	WidgetExactitude* exactitude = new WidgetExactitude(percent);
	exactitude->SetPos(
				(Video::video_->GetWidth()-exactitude->GetWidth())/2.0,
				200);
	AppendWidget(exactitude);

	sprintf(aux, "Exactitude: %f", percent*100);

	info = new WidgetBanner(aux, 30);
	info->SetPos((Video::video_->GetWidth()-info->GetWidth())/2.0, 350);
	AppendWidget(info);

	sprintf(aux, "Notes serie: %i", maxHits);
	info = new WidgetBanner(aux, 30);
	info->SetPos((Video::video_->GetWidth()-info->GetWidth())/2.0, 400);
	AppendWidget(info);
}