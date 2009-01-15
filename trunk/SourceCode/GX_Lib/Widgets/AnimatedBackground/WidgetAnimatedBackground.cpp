#include "WidgetAnimatedBackground.hpp"

#include "Video.hpp"
#include "GX_Graphic.hpp"

#include <string.h>


void WidgetAnimatedBackground::Draw(int x, int y)
// Draw the animated background
{
	if(image_)
	{
		x_ = int(x_ -30 +60*(rand()/(double)RAND_MAX));
//		x_ = x_ -30 +60*drand48();

		if(x_<0)
			x_ = 0;
		else if(x_+image_->GetWidth() > Video::video_->GetWidth())
			x_ = Video::video_->GetWidth() - image_->GetWidth();

		y_ = int(y_ -30 +60*(rand()/(double)RAND_MAX));
//		y_ = y_ -30 +60*drand48();

		if(y_<0)
			y_ = 0;
		else if(y_+image_->GetHeight() > Video::video_->GetHeight())
			y_ = Video::video_->GetHeight() - image_->GetHeight();

		image_->Draw(x+x_, y+y_);
	}
}

void WidgetAnimatedBackground::SetImage(char* path)
// Set an image to the animated background
{
	if(image_)
		delete(image_);

	if(strcmp(path, ""))
		image_ = GX_Graphic::Make(path, 0,0);
	else
		image_ = NULL;
}


WidgetAnimatedBackground::WidgetAnimatedBackground():
	image_(NULL){}

WidgetAnimatedBackground::WidgetAnimatedBackground(char* path):
	image_(NULL)
{
	SetImage(path);
	SetPos(Video::video_->GetWidth()/2.0,
			Video::video_->GetHeight()/2.0);
}

WidgetAnimatedBackground::~WidgetAnimatedBackground()
{
	delete(image_);
}
