#include "WidgetWindow.hpp"

class MainLoop
{
private:
	WidgetWindow* window_;
	WidgetWindow* windowAux_;

	void UpdateWindow();

public:
	static MainLoop* mainLoop_;

	void SetWindow(WidgetWindow* window);
	WidgetWindow* GetWindow();

	MainLoop(WidgetWindow* window);
};
