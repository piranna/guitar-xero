#include "WidgetFretboard.hpp"

#include "Timer.hpp"

#include "ParserOptions.hpp"
#include "GX_Common.hpp"
#include "constants.hpp"

#include "Video.hpp"


void WidgetFretboard::Draw(int x, int y)
{
	// load frets images
	for(int i=-3; i<1; i++)
		fretImage_->Draw(x+x_,
						y+y_
						+ BUTTONS_LINE
						+ i*fretImage_->GetHeight()
						+ (int)((song_->GetBpm()/60.0)
								*(Timer::timer_->GetSongTime()
								*fretImage_->GetHeight()))
								%fretImage_->GetHeight());

	// draw notes and buttons on fretboard
	DrawSong(x_+x, y_+y);
	DrawButtons(x_+x, y_+y);
}

void WidgetFretboard::DrawSong(int x, int y)
{
	float time = Timer::timer_->GetSongTime();

	for(int i=FRET_1; i<=FRET_5; i++)
	{
		Note* note = song_->GetNote((tAction)i);
		while(note)
		{
			if(note->GetFinish() > time-0.5)
				if(note->GetStart() < time+2.0)
					DrawNote(x,y, (tAction)i, note);
				else
					break;

			note = note->GetSig();
		};
	};
}

void WidgetFretboard::DrawNote(int x, int y, tAction cord, Note* note)
{
	float aux = fretImage_->GetWidth()/12.0;	// cord interspace

	int y1 = y+int(BUTTONS_LINE
				+ (song_->GetBpm()/60.0) * fretImage_->GetHeight()
					* (Timer::timer_->GetSongTime() - note->GetStart()));
	int y2 = y+int(BUTTONS_LINE
				+ (song_->GetBpm()/60.0) * fretImage_->GetHeight()
					* (Timer::timer_->GetSongTime() - note->GetFinish()));

	// Draw note

	tColor color = fretColor_[cord];
	if(!(note->IsActive()))				// Note inactive (not pushed)
	{
		color.r = 128;
		color.g = 128;
		color.b = 128;
	}
	else if(!Actions::actions_->GetAction(cord)
			)//&& )	// Note not playing
	{
		color.r = int(color.r*0.9);
		color.g = int(color.g*0.9);
		color.b = int(color.b*0.9);
	};

	fretImage_->Box(x+int((2*(cord+1)-0.5)*aux), y+y2,
					x+int((2*(cord+1)+0.5)*aux), y+y1,
					color.r, color.g, color.b);

	Video::video_->FilledCircle(x+int(2*(cord+1)*aux), y+y1, int(aux),
							color.r, color.g, color.b, 255);

	fretImage_->Circle(x+int(2*(cord+1)*aux), y+y1, int(aux),
						0,0,0);
}

void WidgetFretboard::DrawButtons(int x, int y)
{
	float aux = fretImage_->GetWidth()/12.0;	// cord interspace

	for(int i=0; i<5; i++)
	{
		// buttons
		fretImage_->Circle(x+int(((i+1)*2*aux)), y+BUTTONS_LINE,
							int(aux),
							fretColor_[i].r, fretColor_[i].g,
							fretColor_[i].b);

		// buttons pushed
		if(Actions::Actions::actions_->GetAction((tAction)i))
			Video::video_->FilledCircle(x+int(((i+1)*2*aux)),
										y+BUTTONS_LINE,
										int(aux),
										fretColor_[i].r, fretColor_[i].g,
										fretColor_[i].b, 255);
	};
}


void WidgetFretboard::SetFretImage(char* fretPath)
{
	if(fretImage_)
		delete(fretImage_);

	fretImage_ = GX_Graphic::Make(fretPath, 0,0);
	if(fretImage_)
	{
		// frets
		fretImage_->HLine(0,fretImage_->GetWidth(), 0, 255,255,0);

		// cords
		for(int i=2; i<12; i=i+2)
			fretImage_->VLine(int((i/12.0)*fretImage_->GetWidth()), 0,
								fretImage_->GetHeight(), 255,255,0);
	}
}


WidgetFretboard::WidgetFretboard(Song* song):
	song_(song),
	fretImage_(NULL),
	fretColor_(LoadButtonsColors())
{}

WidgetFretboard::~WidgetFretboard()
{
	delete(fretImage_);
	delete(fretColor_);
}