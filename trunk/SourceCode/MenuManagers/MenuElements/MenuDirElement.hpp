//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef MenuDirElement_hpp
#define MenuDirElement_hpp

#include "MenuEntry.hpp"

#include "GX_Graphic.hpp"


class MenuDirElement: public MenuEntry
{
private:
	char* path_;
	bool isSong_;

	void Draw(int x, int y);

protected:
	GX_Graphic* image_;

	MenuDirElement(char* path, bool isSong);
	~MenuDirElement();

public:
	bool IsSong();
	char* GetPath();
};

#endif
