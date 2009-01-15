#include "VideoConfig.hpp"

#include "compileConfiguration.h"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "Video.hpp"

#include "Configuration.hpp"

#include "MenuContainer.hpp"
#include "WidgetBoolean.hpp"
#include "WidgetLabel.hpp"
#include "WidgetMultiple.hpp"
#include "WidgetSlider.hpp"


void VideoConfig::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new MenuContainer("Video resolution", 30,
							new WidgetMultiple("video", "resolution",
												videoModes_)));

#ifdef SUPPORT_VIDEO_WINDOWING
	host_->Append(new MenuContainer("Fullscreen mode", 30,
							new WidgetBoolean("video", "fullscreen")));
#endif

	host_->Append(NULL);

host_->Append(new WidgetLabel("Smooth quality", 30));
//	host_->Append(new MenuContainer("Smooth quality", 30,
//							new WidgetMultiple()));
host_->Append(new WidgetLabel("SVG quality", 30));
//	host_->Append(new MenuContainer("SVG quality", 30,
//							new WidgetMultiple()));
	host_->Append(new MenuContainer("Text scale", 30,
							new WidgetSlider("video", "fontscale", "1.0")));
	
	host_->Append(NULL);

	host_->Append(new MenuContainer("Graphic library", 30,
					new WidgetMultiple("video", "graphic_library",
										Video::libraries_)));

#ifdef SUPPORT_VIDEO_3D
	if(Video::video_->CanRender3D())
		host_->Append(new MenuContainer("Rendering in 3D", 30,
								new WidgetBoolean("video", "render_3D")));
	else
		host_->Append(new MenuContainer("Rendering in 3D", 30,
						new WidgetBoolean("video", "render_3D", false)));
#endif

	host_->AppendBack();
}

void VideoConfig::ActionBack()
{
	host_->SetMenuData(new Configuration());
}

void VideoConfig::ActionExec(int index)
{
	if(index==0)		// resolution
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();

		Video::video_->InitScreen();

//		Init();
//		VideoConfig();
		return;
	};

#ifdef SUPPORT_VIDEO_WINDOWING
	if(index==1)		// fullscreen
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();

		Actions::actions_->SetAction(SELECT, false);
		Actions::actions_->SetAction(MORE, false);
		Actions::actions_->SetAction(LESS, false);

		Video::video_->InitScreen();
//		Init();
//		VideoConfig();
		return;
	};
#else
	index++;
#endif

	if(index==2)		// smooth quality
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();
		return;
	};

	if(index==3)		// svg quality
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();
		return;
	};

	if(index==4)		// text scale
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();
		return;
	};

	if(index==5)		// graphic library
	{
		((MenuContainer*)host_->Get(index))->ProcessActions();

		Video::Select();

		// Recreate host_ with new graphic library and add data to it
//		delete(host_);
//		host_ = MenuItem::Make(30, 60);

		return;
	};

	if(index==6)		// Render in 3D
	{
		if(Video::video_->CanRender3D())
		{
			((MenuContainer*)host_->Get(index))->ProcessActions();
			return;
		}
		else
			index++;
	};

	ActionBack();
}


VideoConfig::VideoConfig():
	TextMenu(),
	videoModes_(Video::video_->GetVideoModes())
{}

VideoConfig::~VideoConfig()
{
	for(int i=0; videoModes_[i]; i++)
		delete(videoModes_[i]);
	delete(videoModes_);
}