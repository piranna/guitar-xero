//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


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
