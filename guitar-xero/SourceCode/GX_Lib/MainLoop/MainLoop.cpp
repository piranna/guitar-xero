#include "MainLoop.hpp"


#include <stdlib.h>

#include "Timer.hpp"
#include "Input.hpp"
#include "Video.hpp"


MainLoop* MainLoop::mainLoop_ = NULL;

void MainLoop::SetWindow(WidgetWindow* window)
{
	windowAux_ = window;
}

void MainLoop::UpdateWindow()
// Look if it has been defined a new window
// and substitute the old one with the new one
{
	if(windowAux_)
	{
		delete(window_);
		window_ = windowAux_;
		windowAux_ = NULL;
	};
}

WidgetWindow* MainLoop::GetWindow()
// Return the current window
{
	return window_;
}


MainLoop::MainLoop(WidgetWindow* window)
{
	if(!mainLoop_)
	{
		mainLoop_ = this;

		window_ = window;
		windowAux_ = NULL;

		while(true)
		{
			Input::input_->GetActions();
			window_->ProcessActions();

			UpdateWindow();

			window_->Draw(0,0);
			Video::video_->Flip();

			Timer::timer_->UpdateTime();
		};
	};
}
