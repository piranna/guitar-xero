#ifndef GameConfig_hpp
#define GameConfig_hpp

#include "TextMenu.hpp"


class GameConfig: public TextMenu
{
private:
	char** languages_;

	char** GetLanguages();

	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	GameConfig();
	~GameConfig();
};

#endif
