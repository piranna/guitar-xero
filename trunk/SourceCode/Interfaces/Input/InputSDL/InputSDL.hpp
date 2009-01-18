//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef InputSDL_hpp
#define InputSDL_hpp

#include "Input.hpp"

#include "Actions.hpp"

#include "SDL/SDL.h"


class InputSDL: public Input
{
private:
	SDLKey keys_[enumKeys];

	void KeyDown(SDLKey key);
	void KeyUp(SDLKey key);
	SDLKey PyGameKey2SDLKey(char* key);
	void LoadKeys();

public:
	void GetActions();

	tInputMode GetMode();
	void SetMode(tInputMode mode);
	char GetCharacter();
	char* GetKeyName();

	InputSDL(Actions* actions);
};

#endif
