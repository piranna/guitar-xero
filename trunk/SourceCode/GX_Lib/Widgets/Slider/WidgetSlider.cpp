#include "WidgetSlider.hpp"

#include <string.h>
#include <stdlib.h>

#include "ParserOptions.hpp"
#include "constants.hpp"


void WidgetSlider::ProcessActions()
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	float value = atof(parser.GetConfig(block_, option_));

	// Change config
	if(Actions::actions_->GetAction(MORE))
	{
		Actions::actions_->SetAction(MORE, false);
		value = value + 0.05;
		if(value > 1.0)
			value = 1.0;
	};

	if(Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(LESS, false);
		value = value - 0.05;
		if(value < 0.0)
			value = 0.0;
	};

	// Save new configuration
	char textValue[10];
	sprintf(textValue, "%f", value);
	parser.SetConfig(block_, option_, textValue);

	Render();
}

void WidgetSlider::Render()
{
	if(image_)
		delete(image_);

	image_ = GX_Graphic::Make(SLIDER_WIDTH, 30);

	// Render slider
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();
	float value = atof(parser.GetConfig(block_, option_, default_));

	image_->Fill(0, 0,
				int(value*100), int(image_->GetHeight()*0.75),
				255,0,0);

	// Render slider base
	image_->Fill(0, int(image_->GetHeight()*0.75),
				SLIDER_WIDTH, int(image_->GetHeight()*0.25),
				0,0,0);

	// Render text
	float intensity;
	if(focused_)
		intensity = 1.0;
	else
		intensity = 0.75;

	char fontPath[256];
	sprintf(fontPath, "%s/%s", MEDIA_DIR, "laundromat_1967.ttf");
	
	tColor color = {int(255*intensity), int(255*intensity), 0};

	GX_Graphic* text = GX_Graphic::Make(
							parser.GetConfig(block_, option_, default_),
							fontPath, image_->GetHeight(), color);
	image_->Blit(text, int((image_->GetWidth()-text->GetWidth())/2.0), 0);
	delete(text);
}

void WidgetSlider::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}


WidgetSlider::WidgetSlider(char* block, char* option, char* def):
	image_(NULL)
{
	strlcpy(block_, block, 32);
	strlcpy(option_, option, 32);
	strlcpy(default_, def, 32);

	Render();
}

WidgetSlider::~WidgetSlider()
{
	delete(image_);
}
