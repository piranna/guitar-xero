#include "DirMenuManager.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "StartingMenu.hpp"
#include "NoSongs.hpp"

#include "MainLoop.hpp"

#include "Timer.hpp"


void DirMenuManager::Draw(int x, int y)
{
	int i=0;

	ListEntry* entry = host_->GetMenuElements();
	while(entry)
	{
		int posY;

		if(host_->GetIndex() < (int)offset_)		// up menu
		{
			if(i < (int)offset_)					// Over index item
				posY = int(15*(i-offset_));

			else if(i == (int)offset_)				// Indexed item
				posY = int(230 + 230*((int)offset_-offset_));

			else// i > (int)offset_					// Below index
				posY = int(230+15*(i-offset_));
		}

		else if(host_->GetIndex() > (int)offset_)	// down menu
		{
			if(i-1 < (int)offset_)					// Over index item
				posY = int(15*(i-offset_));

			else if(i-1 == (int)offset_)			// Indexed item
				posY = int(230 + 230*((int)offset_-offset_));

			else// i-1 > (int)offset_				// Below index
				posY = int(230+15*(i-offset_));
		}

		else						// menu doesn't move
		{
			if(i <= (int)offset_)
				posY = int(15*(i-offset_));
			else
				posY = int(230+15*(i-offset_));
		};

		((Widget*)entry->GetData())->Draw(x, y+posY);
		entry = entry->GetSig();
		i++;
	};

// without (int) it vibrate, but is the only solution to avoid problems
// with positions... :-(
// This fails with menu up, too.
	if(host_->GetIndex() != offset_)
		offset_ = offset_
				+SELECT_SONG_SCROLL_SPEED
				*(host_->GetIndex() - offset_)
				*Timer::timer_->GetDiffTime();

printf("%f\n", Timer::timer_->GetDiffTime());
}


DirMenuManager::DirMenuManager():
	offset_(0.0)
{}
