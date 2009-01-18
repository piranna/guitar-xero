//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetMultiple.hpp"

#include <string.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "error.h"


void WidgetMultiple::ProcessActions()
{
	int maxOptions = 0;
	while(options_[maxOptions])
		maxOptions++;
	if(!maxOptions)
	{
		ERROR("no options for block");
		return;
	};

	maxOptions--;

	// Get option value from configuration file
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	int numOption = maxOptions;
	while(numOption &&
			(strcmp(parser.GetConfig(block_, option_),
					options_[numOption])!=0))
		numOption--;

	// Change config
	if(Actions::actions_->GetAction(MORE))
	{
		Actions::actions_->SetAction(MORE, false);
		numOption++;
		if(numOption>maxOptions)
			numOption=0;
	};

	if(Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(LESS, false);
		numOption--;
		if(numOption<0)
			numOption=maxOptions;
	};

	// Save new configuration
	parser.SetConfig(block_, option_, options_[numOption]);

	Render();
}

void WidgetMultiple::Render()
{
	// Center text
	if(center_)
		delete(center_);

	// text
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	char text[32];
	strcpy(text, parser.GetConfig(block_, option_, options_[0]));

	// color
	float intensity = INTENSITY_UNFOCUSED;
	if(focused_)
		intensity = 1.0;

	tColor color = {255*intensity, 255*intensity, 0};

	center_ = GX_Graphic::Make(text, MEDIA_DIR, "laundromat_1967.ttf", 30, color);

	// Right arrow
	if(right_)
		delete(right_);

	if(focused_)
	{
		char path[256];
		sprintf(path, "%s/%s", MEDIA_DIR, "right.png");
		right_ = GX_Graphic::Make(path, 0, center_->GetHeight());
	}
	else
		right_=NULL;
}

void WidgetMultiple::Draw(int x, int y)
{
	if(focused_ && left_)
		left_->Draw(x, y);

	if(center_)
		center_->Draw(x + left_->GetWidth(), y);

	if(right_)
		right_->Draw(x + left_->GetWidth() + center_->GetWidth(), y);
}


WidgetMultiple::WidgetMultiple(char* block, char* option, char* options[]):
	MenuElement(block, option),
	left_(NULL), center_(NULL), right_(NULL), options_(options)
{
	Render();

	char path[256];
	sprintf(path, "%s/%s", MEDIA_DIR, "left.png");
	left_ = GX_Graphic::Make(path, 0, center_->GetHeight());
}

WidgetMultiple::~WidgetMultiple()
{
	delete(left_);
	delete(center_);
	delete(right_);
}
