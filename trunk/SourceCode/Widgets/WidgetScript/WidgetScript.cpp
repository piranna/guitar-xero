#include "WidgetScript.hpp"

#include "constants.hpp"

#include "error.h"


void WidgetScript::Draw(int x, int y)
// Draw the current image and/or subtitle, if any
{
	if(image_)
		image_->Draw(x+x_, y+y_);

	if(subtitle_)
		subtitle_->Draw(x+x_, y+y_+BUTTONS_LINE);
}

void WidgetScript::SetImage(char* line)
// Set and render the current image
{
	// Delete old image, if any
	if(image_)
		delete(image_);

	// If line!=null, render the image
	if(strcmp(line, ""))
	{
		image_ = GX_Graphic::Make(line, 0,0);
		if(!image_)
			ERROR("unable to load image " << line);
	}

	// If line==null, set image to null
	else
		image_=NULL;
}

void WidgetScript::SetSubtitle(char* line)
// Set and render the current subtitle
{
	// Delete old subtitle, if any
	if(subtitle_)
		delete(subtitle_);

	// If line!=null, rendet the subtitle
	if(strcmp(line, ""))
	{
		char fontPath[256];
		sprintf(fontPath, "%s/%s", MEDIA_DIR, "laundromat_1967.ttf");
		tColor color = {255, 255, 255};
		subtitle_ = GX_Graphic::Make(line, fontPath, 48, color);
		if(!subtitle_)
			ERROR("unable to render text " << line);
	}

	// If line==null, set subtitle to null
	else
		subtitle_=NULL;
}


void WidgetScript::Move()
// Delete outdated script entries from script head
// and render new script entries if necessary
{
	// While there is a script and script entries are outdated,
	// remove old data
	while(script_
		&& ((script_->start_ + script_->finish_)/1000.0
			< Timer::timer_->GetSongTime()))
	{
		if(script_->type_==TEXTTYPE)
			SetSubtitle("");
		else	// type == PIC
			SetImage("");

		ScriptEntry* aux = script_;
		script_ = script_->sig_;
		delete(aux);
	};

	// While there is script and script entries start time is older
	// than actual time, render new script entries
	ScriptEntry* auxScript = script_;
	while(auxScript
		&& (auxScript->start_/1000.0 < Timer::timer_->GetSongTime()))
	{
		// If script entry has data, render it and set data to null
		if(strcmp(auxScript->text_, ""))
		{
			if(auxScript->type_==TEXTTYPE)
				SetSubtitle(auxScript->text_);
			else		// type == PIC
				SetImage(auxScript->text_);

			strcpy(auxScript->text_, "");
		};

		auxScript = auxScript->sig_;
	};
}


WidgetScript::WidgetScript(ScriptEntry* script):
	script_(script),
	image_(NULL), subtitle_(NULL)
{}

WidgetScript::~WidgetScript()
{
	delete(image_);
	delete(subtitle_);
}