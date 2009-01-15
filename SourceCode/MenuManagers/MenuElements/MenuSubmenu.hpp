#include "MenuElement.hpp"

#include "GX_Graphic.hpp"


class MenuSubmenu: public MenuElement
{
private:
	GX_Graphic* image_;

	void Draw(int x, int y);
	void SetFocus(bool focused);

public:
	MenuSubmenu();
	~MenuSubmenu();
};
