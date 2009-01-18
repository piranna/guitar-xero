//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "SongEditor.hpp"

#include "StartingMenu.hpp"

#include "WidgetLabel.hpp"


void SongEditor::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 30);

	host_->Append(new WidgetLabel("Edit existing songs", 30));
	host_->Append(new WidgetLabel("Import new songs", 30));
	host_->Append(new WidgetLabel("Import Guitar Hero (TM) songs", 30));

	host_->AppendBack();
}

void SongEditor::ActionBack()
{
	host_->SetMenuData(new StartingMenu());
}

void SongEditor::ActionExec(int index)
{
	switch(index)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			ActionBack();
	};
}


SongEditor::SongEditor():
	TextMenu()
{}
