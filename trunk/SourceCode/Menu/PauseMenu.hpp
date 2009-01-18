//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "TextMenu.hpp"

#include "PlaySong.hpp"


class PauseMenu: public TextMenu
{
private:
	PlaySong* playSong_;

	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	PauseMenu(PlaySong* playSong);
};

#endif
