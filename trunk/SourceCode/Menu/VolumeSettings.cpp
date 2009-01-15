#include "VolumeSettings.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "SoundConfig.hpp"
#include "PauseMenu.hpp"

#include "WidgetSlider.hpp"


void VolumeSettings::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new MenuContainer("Guitar Volume", 30,
							new WidgetSlider("audio", "guitarvol", "1.0")));
	host_->Append(new MenuContainer("Song Volume", 30,
							new WidgetSlider("audio", "songvol", "1.0")));
	host_->Append(new MenuContainer("Rhythm Volume", 30,
							new WidgetSlider("audio", "rhythmvol", "1.0")));
	host_->Append(new MenuContainer("Over the sound", 30,
							new WidgetSlider("audio", "screwupvol", "0.25")));

	host_->AppendBack();
}


void VolumeSettings::ActionBack()
{
	if(playSong_)
		host_->SetMenuData(new PauseMenu( playSong_));
	else
		host_->SetMenuData(new SoundConfig());
}

void VolumeSettings::ActionExec(int index)
{
	if(index==host_->GetLength()-1)
		ActionBack();

	else
		((MenuContainer*)host_->Get(index))->ProcessActions();
}


VolumeSettings::VolumeSettings(
								PlaySong* playSong):
	TextMenu(),
	playSong_(playSong){}
