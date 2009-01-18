//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuKey.hpp"

#include <string.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "Timer.hpp"
#include "Input.hpp"


void MenuKey::Blink()
{
	if(int(Timer::timer_->GetGlobalTime()) % 2)	// Blank
	{
		if(image_)
		{
			delete(image_);
			image_=NULL;
		}
	}

	else if(!image_)							// Show
		Render();
}

void MenuKey::ProcessActions()
{
	if(Input::input_->GetMode()==KEYNAME)	// If input mode = KEYNAME
	{										// set key
		char* aux = Input::input_->GetKeyName();
		if(aux)	// If one key have been pressed, set key in config file
		{
			Input::input_->LoadKeys();
			Input::input_->SetMode(EVENT);

			ParserOptions parser(GUITARXERO_INI);
			parser.Read();

			// Set new key
			parser.SetConfig(block_, option_, KeyName2PyGameKey(aux));

			Render();
			return;
		};

		Blink();
	}
	else	// Enable change button - Set KEYNAME input mode
		Input::input_->SetMode(KEYNAME);
}

void MenuKey::Render()
{
	if(image_)
		delete(image_);

	float intensity = INTENSITY_UNFOCUSED;
	if(focused_)
		intensity = 1.0;

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	char text[5];
	strncpy(text, parser.GetConfig(block_, option_, default_), 5);

	tColor color = {255*intensity, 255*intensity, 0};

	image_ = GX_Graphic::Make(text, MEDIA_DIR, "laundromat_1967.ttf", 30, color);
}

void MenuKey::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}


MenuKey::MenuKey(char* block, char* option, char* def):
	MenuElement(block, option),
	image_(NULL)
{
	strlcpy(default_, def, 32);

	Render();
}

MenuKey::~MenuKey()
{
	delete(image_);
}
