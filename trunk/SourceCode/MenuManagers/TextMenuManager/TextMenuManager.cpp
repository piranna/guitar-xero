//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "TextMenuManager.hpp"

#include "Video.hpp"


void TextMenuManager::Draw(int x, int y)
{
	int posY = y;

	int index = host_->GetIndex();

	// Calc displacement
	ListEntry* entry = host_->GetMenuElements();
	int i=0;
	for(; i<index && entry; i++, entry = entry->GetSig())
	{
		if((Widget*)entry->GetData())
			posY = posY + 60;

		else
		{
			posY = posY + 15;
			index++;
		}
	};

	if(posY > (Video::video_->GetHeight() - y))
		posY = Video::video_->GetHeight() - (y+60 + posY);
	else
		posY = 0;


// [TO-DO] Add offset support so displacement can go up

	// Draw menu
	entry = host_->GetMenuElements();
	while(entry)
	{
		Widget* aux = (Widget*)entry->GetData();

		if(aux)
		{
			aux->Draw(x+0, y+posY);
			posY=posY+60;
		}
		else
			posY=posY+15;

		entry = entry->GetSig();
	}
}


TextMenuManager::TextMenuManager()
{}
