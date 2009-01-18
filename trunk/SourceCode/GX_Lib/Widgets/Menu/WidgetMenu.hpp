//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef WidgetMenu_hpp
#define WidgetMenu_hpp

#include "Widget.hpp"

#include "MenuData.hpp"
class MenuData;
#include "MenuManager.hpp"
class MenuManager;


class WidgetMenu: public WidgetPositionable
{
private:
	MenuManager* menuManager_;
	MenuManager* menuManagerAux_;
	MenuData* menuData_;
	MenuData* menuDataAux_;
	List* menuElements_;

	int index_;

	void Draw(int x, int y);
	void UpdateMenu();

public:
	void ProcessActions();
	void ActionBack();
	void ActionExec();
	void ActionNext();
	void ActionPrev();

	void SetMenuManager(MenuManager* menuManager);
	void SetMenuData(MenuData* menuData);

	void Append(Widget* menuElement);
	void AppendBack();

	ListEntry* GetMenuElements();
	ListData* Get(int index);
	int GetIndex();
	int GetLength();

	void Reload();
	void Reset();

	WidgetMenu(MenuManager* menuManager, MenuData* menuData);
};

#endif
