//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "SelectDificulty.hpp"

#include "PlaySong.hpp"

#include "DirMenuManager.hpp"
#include "SongSelector.hpp"

#include "MainLoop.hpp"

#include "WidgetLabel.hpp"


void SelectDificulty::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 48);

	int index = 0;
	for(int i=0; i<enumDificulty; i++)
		if(tracks_[i])
		{
			switch(i)
			{
				case SUPAEASY:
					host_->Append(new WidgetLabel("Supaeasy", 48));
					break;
				case EASY:
					host_->Append(new WidgetLabel("Easy", 48));
					break;
				case MEDIUM:
					host_->Append(new WidgetLabel("Medium", 48));
					break;
				case AMAZING:
					host_->Append(new WidgetLabel("Amazing", 48));
					break;
				default:
					return;
			};

			dificulty_[index] = (tDificulty)i;
			index++;
		};
}

void SelectDificulty::ActionBack()
{
	// Get song path
	char aux[256];
	strlcpy(aux, song_->GetSongPath(), 256);

	// Search last ocurrence of '/' in aux and change it to '\0'
	char* last = strrchr(aux, '/');
	*last = '\0';

	// Delete song_ (we don't need it anymore)
	delete(song_);	// This is done here to use less memory that
					// setting the MenuManager before

	// Change menu and menumanager to song selector
	host_->SetMenuData(new SongSelector( aux));
	host_->SetMenuManager(new DirMenuManager());
}

void SelectDificulty::ActionExec(int index)
{
	if(Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(LESS, false);
		ActionBack();
	}

	else
	{
		song_->ParseMidi(dificulty_[index]);

		MainLoop::mainLoop_->SetWindow(
								new PlaySong( song_));
	}
}


SelectDificulty::SelectDificulty(
								Song* song, bool tracks[enumDificulty]):
	TextMenu(),
	song_(song)
{
	for(int i=0; i<enumDificulty; i++)
		tracks_[i] = tracks[i];

//	char path[256];
//	GetFileExtension(path, MEDIA_DIR, "elvis_lapelvis");
//	video->SetBackground(path);
}
