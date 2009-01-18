//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "NoSongs.hpp"

#include <stdio.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "StartingMenu.hpp"

#include "WidgetLabel.hpp"
#include "WidgetTextbox.hpp"

#include "Actions.hpp"


void NoSongs::Render()
{
//	host_->SetFont("laundromat_1967.ttf", 48);

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	host_->Append(new WidgetLabel("There are no songs", 48));
	host_->Append(new WidgetTextbox("game", "songs_root", 48, SONGS_ROOT));

	host_->AppendBack();
}

void NoSongs::ActionBack()
{
	host_->SetMenuData(new StartingMenu());
}

void NoSongs::ActionExec(int index)
{
	if(Actions::actions_->GetAction(LESS)
		|| index==host_->GetLength()-1)
	{
		Actions::actions_->SetAction(LESS, false);
		ActionBack();
	}

	else	// Edit song root
		((WidgetTextbox*)host_->Get(index))->ProcessActions();
}


NoSongs::NoSongs():
	TextMenu()
{}
