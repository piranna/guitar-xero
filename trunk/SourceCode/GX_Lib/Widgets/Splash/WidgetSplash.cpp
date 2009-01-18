//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "WidgetSplash.hpp"

#include "Timer.hpp"
#include "Video.hpp"

#include <stdio.h>

double WidgetSplash::GetTime()
{
	return splashTime_;
}

void WidgetSplash::Draw(int x, int y)
{
	splashTime_ = splashTime_ + Timer::timer_->GetDiffTime();

	GX_Graphic* aux = image_->GetZoom(splashTime_*image_->GetWidth(),
									splashTime_*image_->GetHeight());
	aux->Draw(int((Video::video_->GetWidth() - aux->GetWidth())/2.0),
			int((Video::video_->GetHeight() - aux->GetHeight())/2.0));

	delete(aux);
}


WidgetSplash::WidgetSplash(GX_Graphic* image):
	image_(image),
	splashTime_(0.0)
{}

WidgetSplash::~WidgetSplash()
{
	delete(image_);
}