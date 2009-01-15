#include "WidgetKeynotes.hpp"

#include "Actions.hpp"


GX_Graphic* WidgetKeynotes::RenderKeyNote(char* name, bool pushed,
						unsigned char r, unsigned char g, unsigned char b)
{
	float intensity = INTENSITY_UNFOCUSED;
	if(pushed)
		intensity = 1.0;

	tColor color={int(r*intensity), int(g*intensity), int(b*intensity)};

	char fontPath[256];
	sprintf(fontPath, "%s/%s", MEDIA_DIR, "laundromat_1967.ttf");
	return GX_Graphic::Make(name, fontPath, 48, color);
}

void WidgetKeynotes::Draw(int x, int y)
{
	for(int i=FRET_1; i<=FRET_5; i++)
		if(keyImage_[i])
			keyImage_[i]->Draw(x_+x+(i*100),y_+y);

	if(keyImage_[NUM_FRETS])
		keyImage_[NUM_FRETS]->Draw(x_+x+200,y_+y+100);
}

void WidgetKeynotes::ProcessActions()
{
	for(int i=FRET_1; i<=FRET_5; i++)
		if(Actions::actions_->GetAction((tAction)i)!=oldAction_[i])
		{
			if(keyImage_[i])
				delete(keyImage_[i]);

			char text[3];
			sprintf(text, "#%i", i+1);
			keyImage_[i] = RenderKeyNote(text,
										Actions::actions_
												->GetAction((tAction)i),
										fretColor_[i].r,
										fretColor_[i].g,
										fretColor_[i].b);
			oldAction_[i] = Actions::actions_->GetAction((tAction)i);
		}

	if(Actions::actions_->GetAction(PICK)!=oldAction_[NUM_FRETS])
	{
			if(keyImage_[NUM_FRETS])
				delete(keyImage_[NUM_FRETS]);

		keyImage_[NUM_FRETS] = RenderKeyNote("PICK",
											Actions::actions_
														->GetAction(PICK),
											0, 255, 255);
		oldAction_[NUM_FRETS] = Actions::actions_->GetAction(PICK);
	}
}


WidgetKeynotes::WidgetKeynotes():
	fretColor_(LoadButtonsColors())
{
	for(int i=0; i<=NUM_FRETS; i++)
	{
		keyImage_[i]=NULL;
		oldAction_[i]=true;
	}
}