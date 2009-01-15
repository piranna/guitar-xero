#include "WidgetBoolean.hpp"

#include <string.h>

#include "ParserOptions.hpp"
#include "constants.hpp"


void WidgetBoolean::ProcessActions()
{
	if(enabled_)
	{
		ParserOptions parser(GUITARXERO_INI);
		parser.Read();

		if(strncmp(parser.GetConfig(block_, option_), "True", 4)==0)
			parser.SetConfig(block_, option_, "False");
		else
			parser.SetConfig(block_, option_, "True");

		Render();
	}
}

void WidgetBoolean::Render()
{
	// Clean up
	if(image_)
		delete(image_);

	// Get data
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	char text[6];
	strlcpy(text, parser.GetConfig(block_, option_, "False"), 6);

	// Get font path
	char fontPath[256];
	sprintf(fontPath, "%s/%s", MEDIA_DIR, "laundromat_1967.ttf");

	// Set color and intensity
	tColor color;

	if(enabled_)
	{
		float intensity = INTENSITY_UNFOCUSED;
		if(focused_)
			intensity = 1.0;

		if(strncmp(text, "True", 4)==0)
		{
			color.r = 0;
			color.g = 255*intensity;
			color.b = 0;
		}
		else
		{
			color.r = 255*intensity;
			color.g = 0;
			color.b = 0;
		}
	}
	else
	{
		color.r = 127;
		color.g = 127;
		color.b = 127;
	}

	// Render
	image_ = GX_Graphic::Make(text, fontPath, 30, color);
}

void WidgetBoolean::Draw(int x, int y)
{
	if(image_)
		image_->Draw(x, y);
}


WidgetBoolean::WidgetBoolean(char* block, char* option, bool enabled):
	image_(NULL), enabled_(enabled)
{
	strlcpy(block_, block, 32);
	strlcpy(option_, option, 32);

	Render();
}

WidgetBoolean::WidgetBoolean(char* block, char* option):
	image_(NULL), enabled_(true)
{
	strlcpy(block_, block, 32);
	strlcpy(option_, option, 32);

	Render();
}

WidgetBoolean::~WidgetBoolean()
{
	delete(image_);
}
