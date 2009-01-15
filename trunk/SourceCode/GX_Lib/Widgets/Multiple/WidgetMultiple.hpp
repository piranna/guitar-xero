#ifndef WidgetMultiple_hpp
#define WidgetMultiple_hpp

#include "MenuElement.hpp"

#include "Actions.hpp"


class WidgetMultiple: public MenuElement
{
private:
	GX_Graphic* left_;
	GX_Graphic* center_;
	GX_Graphic* right_;

	char block_[32];
	char option_[32];

	char** options_;



	void ProcessActions();

	void Render();
	void Draw(int x, int y);

public:
	WidgetMultiple(char* block, char* option, char* options[]);
	~WidgetMultiple();
};

#endif
