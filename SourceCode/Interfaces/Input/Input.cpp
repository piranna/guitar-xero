//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Input.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "compileConfiguration.h"
#include "error.h"

#ifdef SUPPORT_INPUT_SDL
	#include "InputSDL.hpp"
#endif

#include "GX_common.hpp"


Input* Input::input_ = NULL;

char* Input::libraries_[] =
{
	#ifdef SUPPORT_INPUT_SDL
		"SDL",
	#endif
	NULL
};


void Input::Select(Actions* actions)
{

	int option = GetOptionMultiple(libraries_, "input", "input_library");

	#ifdef SUPPORT_INPUT_SDL
		if(option==0)
			input_ = new InputSDL(actions);
		return;
	#endif

	FATAL("No input libraries defined in source code!!!");
}


void Input::GetActionKeyDown(tKey key)
{
	switch(key)
	{
		case key_action1:
			actions_->SetAction(SELECT, true);
			actions_->SetAction(PICK, true);
			break;
		case key_action2:
			actions_->SetAction(PICK, true);
			break;

		case key_1:
			actions_->SetAction(FRET_1, true);
			break;
		case key_2:
			actions_->SetAction(FRET_2, true);
			break;
		case key_3:
			actions_->SetAction(FRET_3, true);
			break;
		case key_4:
			actions_->SetAction(FRET_4, true);
			break;
		case key_5:
			actions_->SetAction(FRET_5, true);
			break;

		case key_left:
			actions_->SetAction(LESS, true);
			break;
		case key_right:
			actions_->SetAction(MORE, true);
			break;
		case key_up:
			actions_->SetAction(UP, true);
			break;
		case key_down:
			actions_->SetAction(DOWN, true);
			break;

		case key_cancel:
			actions_->SetAction(BACK, true);
			break;

//		case key_ESCAPE:
//			actions_->SetAction(TILT, true);
//			break;
//		case key_ESCAPE:
//			actions_->SetAction(VIBRATTO, true);
//			break;
	}
}

void Input::GetActionKeyUp(tKey key)
{
	switch(key)
	{
		case key_action1:
			actions_->SetAction(SELECT, false);
			actions_->SetAction(PICK, false);
			break;
		case key_action2:
			actions_->SetAction(PICK, false);
			break;

		case key_1:
			actions_->SetAction(FRET_1, false);
			break;
		case key_2:
			actions_->SetAction(FRET_2, false);
			break;
		case key_3:
			actions_->SetAction(FRET_3, false);
			break;
		case key_4:
			actions_->SetAction(FRET_4, false);
			break;
		case key_5:
			actions_->SetAction(FRET_5, false);
			break;

		case key_left:
			actions_->SetAction(LESS, false);
			break;
		case key_right:
			actions_->SetAction(MORE, false);
			break;
		case key_up:
			actions_->SetAction(UP, false);
			break;
		case key_down:
			actions_->SetAction(DOWN, false);
			break;

		case key_cancel:
			actions_->SetAction(BACK, false);
			break;

//		case key_ESCAPE:
//			actions_->SetAction(TILT, false);
//			break;
//		case key_ESCAPE:
//			actions_->SetAction(VIBRATTO, false);
//			break;
	}
}


Input::Input(Actions* actions):
// It's necesary to specify an 'Actions' object to ensure it is create.
// Really it's not mandatory since actions can be accesed by Actions::actions_,
// but is made as a safer since you need it to be created
// if you want to use inputs
	actions_(actions),
	character_('\0'),
	keyName_(NULL),
	mode_(EVENT)
{};
