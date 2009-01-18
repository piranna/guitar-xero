//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetExactitude.hpp"

#include "GX_Graphic.hpp"

#include <string.h>

#include "common.hpp"
#include "constants.hpp"
#include "defaults.h"


void WidgetExactitude::Draw(int x, int y)
{
	int auxWidth=0;
	int i = 0;

	if(star2_)
		while(i <= 5*percent_-0.5)
		{
			star2_->Draw(x_+x+auxWidth, y_+y);
			auxWidth = auxWidth + star2_->GetWidth();
			i++;
		}

	if(star1_)
		while(i < 5)
		{
			star1_->Draw(x_+x+auxWidth, y_+y);
			auxWidth = auxWidth + star1_->GetWidth();
			i++;
		}
}

int WidgetExactitude::GetWidth()
{
	return 5*star1_->GetWidth();
}

int WidgetExactitude::GetHeight()
{
	return star1_->GetHeight();
}


WidgetExactitude::WidgetExactitude(float percent):
	star1_(NULL), star2_(NULL), percent_(percent)
{
	char aux[256];

	GetFileExtension(aux, MEDIA_DIR, "star1");
	star1_ = GX_Graphic::Make(aux, 0,0);

	GetFileExtension(aux, MEDIA_DIR, "star2");
	star2_ = GX_Graphic::Make(aux, 0,0);
}

WidgetExactitude::~WidgetExactitude()
{
	delete(star1_);
	delete(star2_);
}