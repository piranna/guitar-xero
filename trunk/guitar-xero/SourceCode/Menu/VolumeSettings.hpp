#ifndef VolumeSettings_hpp
#define VolumeSettings_hpp

#include "TextMenu.hpp"

#include "PlaySong.hpp"


class VolumeSettings: public TextMenu
{
private:
	PlaySong* playSong_;

	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	VolumeSettings( PlaySong* playSong);
};

#endif
