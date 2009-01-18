//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "SoundConfig.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"
#include "defaults.h"

#include "Audio.hpp"

#include "VolumeSettings.hpp"
#include "Configuration.hpp"

#include "MenuContainer.hpp"
#include "MenuSubmenu.hpp"
#include "WidgetMultiple.hpp"
#include "WidgetBoolean.hpp"


void SoundConfig::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new MenuContainer("Volumen settings", 30,
									new MenuSubmenu()));
	host_->Append(new MenuContainer("Stereo", 30,
								new WidgetBoolean("audio", "stereo")));
host_->Append(new WidgetLabel("Audio/Video lag", 30));
//	host_->Append(new MenuContainer("Audio/Video lag", 30,
//								new WidgetMultiple("audio", "delay",
//								)));
	host_->Append(new MenuContainer("Sample frequency", 30,
					new WidgetMultiple("audio", "frequency",
										Audio::frequencies_)));
	host_->Append(new MenuContainer("Sample bits", 30,
							new WidgetMultiple("audio", "bits",
												Audio::bits_)));
	host_->Append(new MenuContainer("Buffer size", 30,
					new WidgetMultiple("audio", "buffersize",
										Audio::bufferSizes_)));

	host_->Append(NULL);

	host_->Append(new MenuContainer("Audio library", 30,
					new WidgetMultiple("audio", "audio_library",
										Audio::libraries_)));

	host_->AppendBack();
}

void SoundConfig::ActionBack()
{
	host_->SetMenuData(new Configuration());
}

void SoundConfig::ActionExec(int index)
{
	switch(index)
	{
		case 0:
			if(Actions::actions_->GetAction(MORE) ||
				Actions::actions_->GetAction(SELECT))
			{
				Actions::actions_->SetAction(MORE, false);
				Actions::actions_->SetAction(SELECT, false);

				host_->SetMenuData(new VolumeSettings(
														NULL));
			};
			break;
		case 1:		// Stereo
			((MenuContainer*)host_->Get(index))->ProcessActions();
			break;
		case 2:		// Audio/Video lag
			{
			}
			break;
		case 3:	case 4:	case 5:	case 6:		// Audio library
			((MenuContainer*)host_->Get(index))->ProcessActions();
			break;

		default:	// Back
			ActionBack();
	}
}


SoundConfig::SoundConfig():
	TextMenu()
{}
