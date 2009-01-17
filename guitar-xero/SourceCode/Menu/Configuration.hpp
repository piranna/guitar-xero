#ifndef Configuration_hpp
#define Configuration_hpp

#include "TextMenu.hpp"


class Configuration: public TextMenu
{
private:
	void Render();

	void ActionBack();
	void ActionExec(int index);

public:
	Configuration();
};

#endif
