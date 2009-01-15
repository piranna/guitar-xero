#ifndef VideoConfig_hpp
#define VideoConfig_hpp

#include "TextMenu.hpp"


class VideoConfig: public TextMenu
{
private:
	char** videoModes_;

	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	VideoConfig();
	~VideoConfig();
};

#endif
