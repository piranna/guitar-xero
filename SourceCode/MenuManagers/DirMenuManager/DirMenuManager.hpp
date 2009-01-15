#ifndef SelectSong_hpp
#define SelectSong_hpp

#include "MenuManager.hpp"


class DirMenuManager: public MenuManagerVertical
{
private:
	float offset_;

	void Draw(int x, int y);

public:
	DirMenuManager();
};

#endif
