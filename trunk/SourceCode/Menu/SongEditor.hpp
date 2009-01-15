#ifndef SongEditor_hpp
#define SongEditor_hpp

#include "TextMenu.hpp"


class SongEditor: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	SongEditor();
};

#endif
