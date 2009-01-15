#include "ControlConfig.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"
#include "defaults.h"
#include "TryKeys.hpp"

#include "MainLoop.hpp"

#include "Input.hpp"

#include "Configuration.hpp"
#include "TextMenu.hpp"

#include "MenuContainer.hpp"
#include "MenuSubmenu.hpp"
#include "WidgetMultiple.hpp"

#include "MenuKey.hpp"


void ControlConfig::Render()	// Control config
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new MenuContainer("Try keys", 30, new MenuSubmenu()));

	host_->Append(NULL);

	host_->Append(new MenuContainer("Action", 30,
									new MenuKey("player", "key_action1",
												KEY_ACTION1)));
	host_->Append(new MenuContainer("Second action", 30,
									new MenuKey("player", "key_action2",
												KEY_ACTION2)));

	host_->Append(NULL);

	host_->Append(new MenuContainer("Fret #1", 30,
								new MenuKey("player", "key_1", KEY_1)));
	host_->Append(new MenuContainer("Fret #2", 30,
								new MenuKey("player", "key_2",KEY_2)));
	host_->Append(new MenuContainer("Fret #3", 30,
								new MenuKey("player", "key_3", KEY_3)));
	host_->Append(new MenuContainer("Fret #4", 30,
								new MenuKey("player", "key_4", KEY_4)));
	host_->Append(new MenuContainer("Fret #5", 30,
								new MenuKey("player", "key_5", KEY_5)));

	host_->Append(NULL);

	host_->Append(new MenuContainer("Move left", 30,
									new MenuKey("player", "key_left",
												KEY_LEFT)));
	host_->Append(new MenuContainer("Move right", 30,
									new MenuKey("player", "key_right",
												KEY_RIGHT)));
	host_->Append(new MenuContainer("Move up", 30,
									new MenuKey("player", "key_up",
												KEY_UP)));
	host_->Append(new MenuContainer("Move down", 30,
									new MenuKey("player", "key_down",
												KEY_DOWN)));
	host_->Append(new MenuContainer("Cancel", 30,
									new MenuKey("player", "key_cancel",
											KEY_CANCEL)));

	host_->Append(NULL);

	host_->Append(new MenuContainer("Input library", 30,
						new WidgetMultiple("player", "input_library",
											Input::libraries_)));

	host_->AppendBack();
}

void ControlConfig::ActionBack()
{
	host_->SetMenuData(new Configuration());
}

void ControlConfig::ActionExec(int index)
{
	switch(index)
	{
		case 0:		// Try keys
			if(Actions::actions_->GetAction(SELECT) ||
				Actions::actions_->GetAction(MORE))
			{
//				video->SetAnimator(new FadeIn(-300000, 60));
				MainLoop::mainLoop_->SetWindow(new TryKeys());
			};
			break;
		case 1: case 2: case 3: case 4: case 5: case 6:		// Set keys
		case 7: case 8: case 9: case 10: case 11: case 12:
		{
			ParserOptions parser(GUITARXERO_INI);
			parser.Read();

			// Store old key config
			char oldConfig[32];

			if(Input::input_->GetMode()==KEYNAME)
				strcpy(oldConfig, parser.GetConfig("player",
												tKey2Char(tKey(index))));

			((MenuContainer*)host_->Get(index))->ProcessActions();

			// Swap keys if defined before
			if(Input::input_->GetMode()==EVENT)
;//				for(int i=0; i<enumKeys; i++)
//					if(i != (index-1)
//					and strcmp(parser.GetConfig("player",
//												tKey2Char(tKey(index))),
//							parser.GetConfig("player", tKey2Char(tKey(i))))
//						==0)
//					{
//						parser.SetConfig("player",
//										tKey2Char(tKey(i)),
//										oldConfig);
//
//						//Render();
//
//						//break;
//					};
		}
		break;
		case 13:	// Input library
			((MenuContainer*)host_->Get(index))->ProcessActions();
			break;

		default:	// Back
//			video->SetAnimator(new FadeOut(-300000, 60));
			ActionBack();
	}
}


ControlConfig::ControlConfig():
	TextMenu()
{}
