//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


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
