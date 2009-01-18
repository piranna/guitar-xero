//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetTextbox.hpp"

#include <string.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "Timer.hpp"
#include "Input.hpp"


void WidgetTextbox::Blink()
{
	if(int(Timer::timer_->GetGlobalTime()) % 2
		&& visibleValue_)
	{
		visibleValue_[cursor_] = 'A';
		Render();

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
	// If mode == TEXTMODE, get text
	if(Input::input_->GetMode()==TEXTMODE)
	{
		// If a key have been pushed,
		// modify value_ with new inputs
		char aux = Input::input_->GetCharacter();
		if(aux)
		{
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
				// Decrease cursor_ and move characters from cursor position
				{
					cursor_--;
					char* pBackspace = &(value_[cursor_]);
					Unhead(pBackspace, 1);
				}

//				case 127:	// supr
//				// Move characters from cursor position
//				{
//					char* pBackspace = &(value_[cursor_]);
//					Unhead(pBackspace, 1);
//				}

				default:	// normal characters
				// Append character and increase cursor_
				{
					printf("key: %i, %c.\n", aux, aux);

					Append(value_, aux);
					cursor_++;
				}
			}

			// Set visible value
			if(visibleValue_)
				delete(visibleValue_);
			visibleValue_ = new char[256];
			strncpy(visibleValue_, value_, 256);
		}

		// If character == return or character == escape
		if(aux==13 || aux==27)
			Render();
		else
			Blink();
	}

	else	// Set cursor to value_ lenght and set mode to TEXTMODE
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

	image_ = GX_Graphic::Make(visibleValue_, MEDIA_DIR, "laundromat_1967.ttf", fontSize_, color);
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
	MenuElement(block, option),
	image_(NULL), fontSize_(size), cursor_(0)
{
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
