//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetLifebar.hpp"

#include "constants.hpp"

#include "Video.hpp"

#include "GX_Common.hpp"


void WidgetLifebar::RenderPoints()
{
	if(pointsSurface_)
		delete(pointsSurface_);

	tColor color = Char2tColor(LoadTheme("base_color", "#FFFF80"));

	char aux[10];
	sprintf(aux, "%d", points_);

	pointsSurface_ = GX_Graphic::Make(aux, MEDIA_DIR, "laundromat_1967.ttf", 30, color);
}

void WidgetLifebar::RenderMultiplier()
{
	if(multiplierSurface_)
		delete(multiplierSurface_);

	tColor color = Char2tColor(LoadTheme("base_color", "#FFFF80"));

	char aux[10];
	sprintf(aux, "%dx", multiplier_);

	multiplierSurface_ = GX_Graphic::Make(aux, MEDIA_DIR, "laundromat_1967.ttf", 30, color);
}

void WidgetLifebar::ShowMultiplier()
{
	char aux[256];
	sprintf(aux, "%s/%ix.png", MEDIA_DIR, multiplier_);

	if(splash_)
		delete(splash_);
	splash_ = new WidgetSplash(GX_Graphic::Make(aux, 0,0));
}

void WidgetLifebar::DrawHits(int x, int y)
{
	// Set Hits color
	tColor color;
	switch(multiplier_)
	{
		case 1:	// Green
			color.r = 0;
			color.g = 255;
			color.b = 0;
			break;
		case 2:	// Red
			color.r = 255;
			color.g = 0;
			color.b = 0;
			break;
		case 3:	// Yellow
			color.r = 255;
			color.g = 255;
			color.b = 0;
			break;
		case 4:	// Blue
			color.r = 0;
			color.g = 0;
			color.b = 255;
			break;
	};

	// Draw Hits
	for(int i=0; i<9; i++)
	{
		float intensity=0.5;

		if((mirrored_ && (9-i < hitsSerie_%10))
		|| (!mirrored_ && (i < hitsSerie_%10)))
			intensity=1.0;

		Video::video_->FilledCircle(x+i*16,
					y + int((multiplierSurface_->GetHeight() - 8)/2.0),
					8,
					int(color.r*intensity),
					int(color.g*intensity),
					int(color.b*intensity),
					255);
	}
}

void WidgetLifebar::Draw(int x, int y)
{
	pointsSurface_->Draw(x+x_, y+y_);
	multiplierSurface_->Draw(x + x_, y + y_ + pointsSurface_->GetHeight());

	DrawHits(x+x_ + multiplierSurface_->GetWidth(),
			y+y_ + pointsSurface_->GetHeight());

	if(splash_)
	{
		splash_->Draw(x+x_, y+y_);

		if(splash_->GetTime() > 1.0)
		{
			delete(splash_);
			splash_ = NULL;
		};
	}
}

void WidgetLifebar::AddPoints(float seconds)
{
	points_ = points_
			+ int(seconds
				*POINTS_PER_SECOND
				*multiplier_);

	RenderPoints();
}

void WidgetLifebar::AddHit()
{
	points_ = points_+POINTS_PER_NOTE;
	RenderPoints();

	hits_++;
	hitsSerie_++;
	if(hitsSerie_>maxHits_)
		maxHits_ = hitsSerie_;

	if(hitsSerie_%10 == 0)
		AddMultiplier();
}

void WidgetLifebar::AddMultiplier()
{
	if(multiplier_ < 4)
	{
		multiplier_++;
		RenderMultiplier();

		ShowMultiplier();
	};
}

void WidgetLifebar::ResetHits()
{
	hitsSerie_=0;
	multiplier_=1;

	RenderMultiplier();
}

int WidgetLifebar::GetPoints()
{
	return points_;
}

int WidgetLifebar::GetHits()
{
	return hits_;
}

int WidgetLifebar::GetMaxHits()
{
	return maxHits_;
}


WidgetLifebar::WidgetLifebar():
	
	points_(0),
	hits_(0),
	hitsSerie_(0),
	maxHits_(0),
	multiplier_(1),
	mirrored_(false),
	pointsSurface_(NULL),
	multiplierSurface_(NULL),
	splash_(NULL)
{
	RenderPoints();
	RenderMultiplier();
}

WidgetLifebar::~WidgetLifebar()
{
	delete(pointsSurface_);
	delete(multiplierSurface_);
	delete(splash_);
}
