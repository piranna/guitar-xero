#include "WidgetTextbox.hpp"

#include <string.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "Timer.hpp"
#include "Input.hpp"


void WidgetTextbox::Blink()
{
	if(int(Timer::timer_->GetGlobalTime()) % 2)
	{
		if(visibleValue_)
		{
			visibleValue_[cursor_] = 'A';
			Render();
		}
		delete(visibleValue_);
		visibleValue_=NULL;
	}
	else if(!visibleValue_)
	{
		visibleValue_ = new char[256];
		strncpy(visibleValue_, value_, 256);
		Render();
	}
}

void WidgetTextbox::ProcessActions()
{
	if(Input::input_->GetMode()==TEXTMODE)	// Save changed button
	{
		char aux = Input::input_->GetCharacter();
		if(aux)
		{
			// Modify value_ with new inputs
			switch(aux)
			{
				case 13:	// return
				// Set input mode to event and write to config file
				{
					Input::input_->SetMode(EVENT);

					ParserOptions parser(GUITARXERO_INI);
					parser.Read();
					parser.SetConfig(block_, option_, value_);
				}
				break;

				case 27:	// escape
				// Set input mode to event and get original value
				{
					Input::input_->SetMode(EVENT);

					ParserOptions parser(GUITARXERO_INI);
					parser.Read();
					strncpy(value_, parser.GetConfig(block_, option_,
													default_), 256);
				}

				case 127:	// backspace
				// Decrease cursor_ and move characters
				{
					cursor_--;
					char* pBackspace = &(value_[cursor_]);
					Unhead(pBackspace, 1);
				}

				default:
				// Append character and increase cursor_
				{
					printf("key: %i, %c.\n", aux, aux);

					Append(value_, aux);
					cursor_++;
				}
			}

			// Init visible value
			if(visibleValue_)
				delete(visibleValue_);
			visibleValue_ = new char[256];
			strncpy(visibleValue_, value_, 256);
		}

		if(aux==13 || aux==27)
			Render();
		else
			Blink();
	}

	else	// Enable change button
	{
		cursor_ = strlen(value_);
		Input::input_->SetMode(TEXTMODE);
	}
}

void WidgetTextbox::Render()
{
	if(image_)
		delete(image_);

	float intensity = INTENSITY_UNFOCUSED;
	if(focused_)
		intensity = 1.0;

	tColor color = {255*intensity, 255*intensity, 0};
	char fontPath[256];
	sprintf(fontPath, "%s/%s", MEDIA_DIR, "laundromat_1967.ttf");

	image_ = GX_Graphic::Make(visibleValue_, fontPath, fontSize_, color);
}

//void WidgetTextbox::Draw(int x, int y, int w, int h)
void WidgetTextbox::Draw(int x, int y)
{
//	if(w<image_->GetWidth())
//		image_->DrawTail(x, y, w, h);

	if(image_)
		image_->Draw(x, y);
}


WidgetTextbox::WidgetTextbox(char* block, char* option,
							unsigned char size, char* def):
	image_(NULL), fontSize_(size), cursor_(0)
{
	strlcpy(block_, block, 32);
	strlcpy(option_, option, 32);
	strlcpy(default_, def, 32);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	strncpy(value_, parser.GetConfig(block_, option_, default_), 256);
	visibleValue_ = new char[256];
	strncpy(visibleValue_, value_, 256);

	Render();
}

WidgetTextbox::~WidgetTextbox()
{
	delete(image_);
}
