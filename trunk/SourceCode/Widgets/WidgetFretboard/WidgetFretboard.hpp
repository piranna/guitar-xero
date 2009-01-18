//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetFretboard_hpp
#define WidgetFretboard_hpp

#include "Widget.hpp"

#include "Song.hpp"
#include "Actions.hpp"

#include "GX_Graphic.hpp"


class WidgetFretboard: public WidgetPositionable
{
private:
	Song* song_;


	GX_Graphic* fretImage_;
	tColor* fretColor_;

	void Draw(int x, int y);

	void DrawSong(int x, int y);
	void DrawNote(int x, int y, tAction cord, Note* note);
	void DrawButtons(int x, int y);

public:
	void SetFretImage(char* fretPath);

	WidgetFretboard(Song* song);
	~WidgetFretboard();
};

#endif
