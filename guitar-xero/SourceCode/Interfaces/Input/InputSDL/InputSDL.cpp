#include "InputSDL.hpp"

#include <stdlib.h>

#include "ParserOptions.hpp"
#include "constants.hpp"
#include "defaults.h"

#include "error.h"


void InputSDL::KeyDown(SDLKey key)
{
	for(int i=0; i<enumKeys; i++)
		if(key==keys_[i])
		{
			GetActionKeyDown((tKey)i);
			break;
		};
}

void InputSDL::KeyUp(SDLKey key)
{
	for(int i=0; i<enumKeys; i++)
		if(key==keys_[i])
		{
			GetActionKeyUp((tKey)i);
			break;
		};
}

void InputSDL::GetActions()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
		switch(event.type)
		{
			// mouse
//			case SDL_MOUSEMOTION:
//				break;
//			case SDL_MOUSEBUTTONDOWN:
//				break;

			// keyboard
			case SDL_KEYDOWN:
				switch(mode_)
				{
					case EVENT:
						KeyDown(event.key.keysym.sym);
						break;
					case TEXTMODE:
						if(event.key.keysym.unicode < 0x80
								&& event.key.keysym.unicode > 0)
							character_ = (char)event.key.keysym.unicode;
						break;
					case KEYNAME:
						keyName_ = SDL_GetKeyName(event.key.keysym.sym);
						break;
				};
				break;
			case SDL_KEYUP:
				KeyUp(event.key.keysym.sym);
				break;

			// various
			case SDL_QUIT:
				exit(0);
		}
}

SDLKey InputSDL::PyGameKey2SDLKey(char* key)
{
	if(strcmp(key, "K_RETURN")==0)	return(SDLK_RETURN);
	if(strcmp(key, "K_RSHIFT")==0)	return(SDLK_RSHIFT);
	if(strcmp(key, "K_F1")==0)		return(SDLK_F1);
	if(strcmp(key, "K_F2")==0)		return(SDLK_F2);
	if(strcmp(key, "K_F3")==0)		return(SDLK_F3);
	if(strcmp(key, "K_F4")==0)		return(SDLK_F4);
	if(strcmp(key, "K_F5")==0)		return(SDLK_F5);
	if(strcmp(key, "K_F6")==0)		return(SDLK_F6);
	if(strcmp(key, "K_F7")==0)		return(SDLK_F7);
	if(strcmp(key, "K_F8")==0)		return(SDLK_F8);
	if(strcmp(key, "K_F9")==0)		return(SDLK_F9);
	if(strcmp(key, "K_F10")==0)		return(SDLK_F10);
	if(strcmp(key, "K_F11")==0)		return(SDLK_F11);
	if(strcmp(key, "K_F12")==0)		return(SDLK_F12);
	if(strcmp(key, "K_F13")==0)		return(SDLK_F13);
	if(strcmp(key, "K_F14")==0)		return(SDLK_F14);
	if(strcmp(key, "K_F15")==0)		return(SDLK_F15);
	if(strcmp(key, "275")==0)		return(SDLK_LEFT);
	if(strcmp(key, "276")==0)		return(SDLK_RIGHT);
	if(strcmp(key, "K_UP")==0)		return(SDLK_UP);
	if(strcmp(key, "K_DOWN")==0)	return(SDLK_DOWN);
	if(strcmp(key, "K_ESCAPE")==0)	return(SDLK_ESCAPE);

	ERROR("unknown keycode '" << key << "'");
	return (SDLKey)NULL;
}

void InputSDL::LoadKeys()
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	keys_[key_action1] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_action1", KEY_ACTION1));
	keys_[key_action2] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_action2", KEY_ACTION2));
	keys_[key_1] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_1", KEY_1));
	keys_[key_2] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_2", KEY_2));
	keys_[key_3] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_3", KEY_3));
	keys_[key_4] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_4", KEY_4));
	keys_[key_5] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_5", KEY_5));
	keys_[key_left] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_left", KEY_LEFT));
	keys_[key_right] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_right", KEY_RIGHT));
	keys_[key_up] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_up", KEY_UP));
	keys_[key_down] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_down", KEY_DOWN));
	keys_[key_cancel] = PyGameKey2SDLKey(parser.GetConfig("player",
											"key_cancel", KEY_CANCEL));
}

tInputMode InputSDL::GetMode()
{
	return mode_;
}

void InputSDL::SetMode(tInputMode mode)
{
	SDL_EnableUNICODE(0);
	actions_->ResetActions();

	mode_ = mode;

	switch(mode)
	{
		case EVENT:
			break;
		case TEXTMODE:
			SDL_EnableUNICODE(1);
			character_ = '\0';
			break;
		case KEYNAME:
			keyName_ = NULL;
			break;
	}
}

char InputSDL::GetCharacter()
{
	char aux = character_;
	character_='\0';
	return aux;
}

char* InputSDL::GetKeyName()
{
	char* aux = keyName_;
	keyName_=NULL;
	return aux;
}


InputSDL::InputSDL(Actions* actions):
	Input(actions)
{
	LoadKeys();

//	SDL_ShowCursor(SDL_ENABLE);
//	SDL_ShowCursor(SDL_DISABLE);
}