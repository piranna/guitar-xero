#ifndef WidgetLifebar_hpp
#define WidgetLifebar_hpp

#include "Widget.hpp"

#include "Timer.hpp"

#include "GX_Graphic.hpp"
#include "WidgetSplash.hpp"


class WidgetLifebar: public WidgetPositionable
{
private:
	long points_;
	int multiplier_;
	int hits_;
	int hitsSerie_;
	int maxHits_;
	bool mirrored_;

	GX_Graphic* pointsSurface_;
	GX_Graphic* multiplierSurface_;
	WidgetSplash* splash_;

	void DrawHits(int x, int y);
	void Draw(int x, int y);

	void AddMultiplier();

	void RenderPoints();
	void RenderMultiplier();
	void ShowMultiplier();

public:
	void AddPoints(float seconds);
	void AddHit();
	void ResetHits();

	int GetPoints();
	int GetHits();
	int GetMaxHits();

	WidgetLifebar();
	~WidgetLifebar();
};

#endif
