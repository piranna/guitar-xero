//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef Script_hpp
#define Script_hpp

#include "Widget.hpp"

#include "GX_Graphic.hpp"

#include "Song.hpp"
#include "Timer.hpp"


class WidgetScript: public WidgetPositionable
{
private:
	ScriptEntry* script_;

	GX_Graphic* image_;
	GX_Graphic* subtitle_;

	void Draw(int x, int y);

	void SetImage(char* line);
	void SetSubtitle(char* line);

public:
	void Move();

	WidgetScript(ScriptEntry* script);
	~WidgetScript();
};

#endif
