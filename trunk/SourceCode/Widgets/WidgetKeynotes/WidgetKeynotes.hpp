#include "Widget.hpp"

#include "GX_Common.hpp"
#include "common.hpp"

#include "GX_Graphic.hpp"

#include "constants.hpp"


class WidgetKeynotes: public WidgetPositionable
{
private:
	tColor* fretColor_;

	GX_Graphic* keyImage_[NUM_FRETS+1];
	bool oldAction_[NUM_FRETS+1];

	GX_Graphic* RenderKeyNote(char* name, bool pushed,
					unsigned char r, unsigned char g, unsigned char b);
	void Draw(int x, int y);

public:
	void ProcessActions();

	WidgetKeynotes();
};