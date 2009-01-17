#include "WidgetWindow.hpp"

void WidgetWindow::AppendWidget(Widget* widget)
{
	if(widget)
		widgets_->Append(widget);
}

void WidgetWindow::RemoveLastWidget()
{
	widgets_->RemoveLast();
}

void WidgetWindow::Draw(int x, int y)
{
	ListEntry* entry = widgets_->GetList();
	while(entry)
	{
		Widget* aux = (Widget*)entry->GetData();
		if(aux)
			aux->Draw(x+x_, y+y_);
		entry = entry->GetSig();
	}
}


WidgetWindow::WidgetWindow(): widgets_(new List()){}

WidgetWindow::~WidgetWindow()
{
	delete(widgets_);
}