#ifndef SelectDificulty_hpp
#define SelectDificulty_hpp

#include "TextMenu.hpp"

#include "Song.hpp"


class SelectDificulty: public TextMenu
{
private:
	Song* song_;
	bool tracks_[enumDificulty];
	tDificulty dificulty_[enumDificulty];

	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	SelectDificulty( Song* song,
					bool tracks[enumDificulty]);
};

#endif
