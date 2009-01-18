//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "List.hpp"

#include <stdlib.h>


// ListEntry
void ListEntry::SetSig(ListEntry* sig)
// Set sig list entry
{
	sig_ = sig;
}

ListEntry* ListEntry::GetSig()
// Get sig list entry
{
	return sig_;
}

void ListEntry::SetData(ListData* data)
// Set list entry data. If is diferent of null, overwrite it
{
	if(data_)
		delete(data_);

	data_ = data;
}

ListData* ListEntry::GetData()
// Get list entry data
{
	return data_;
}

ListEntry::ListEntry(ListData* data):
	data_(data),
	sig_(NULL)
{}

ListEntry::~ListEntry()
{
	delete(data_);
}


// List
void List::Reset()
// Delete all list entries from the list
{
	while(head_)
	{
		ListEntry* aux = head_;
		head_ = aux->GetSig();
		delete(aux);
	};
}

void List::Append(ListData* data)
// Add a list entry at the end of the list
{
	if(head_)
	{
		ListEntry* aux = head_;
		while(aux->GetSig())
			aux = aux->GetSig();
		aux->SetSig(new ListEntry(data));
	}
	else
		head_ = new ListEntry(data);
}

void List::RemoveLast()
// Remove last list entry
{
	if(head_)
		if(head_->GetSig())
		{
			ListEntry* aux = head_;
			while(aux->GetSig()->GetSig())
				aux = aux->GetSig();

			delete(aux->GetSig());
			aux->SetSig(NULL);
		}
		else
		{
			delete(head_);
			head_=NULL;
		}
}

void List::Set(int pos, ListData* data)
// Set a list entry position
{
	ListEntry* aux = head_;
	if(aux)
	{
		int i=0;

		while(i<pos && aux->GetSig())
		{
			if(aux->GetData())		// If there's data increment the entry
				i++;				// pos counter. This is done to help
			aux = aux->GetSig();	// the graphic menus blank lines.
		};

		while(!aux->GetData() && aux->GetSig())
			aux = aux->GetSig();

		if(i==pos)				// If we get the position, set data
			aux->SetData(data);
		else if(aux->GetSig())	// else set next position
			aux->GetSig()->SetData(data);
		else
			aux->SetSig(new ListEntry(data));
	}
	else
		head_ = new ListEntry(data);
}

ListEntry* List::GetList()
// Get list head
{
	return head_;
}

ListData* List::GetData(int option)
// Get a list entry data
{
	ListEntry* item = head_;
	if(item)
	{
		int i=0;
		while(i<option && item->GetSig())	// Search the wished item
		{									// while there are enough
			item = item->GetSig();
			if(item->GetData())
				i++;
		}

		if(i==option)	// If 'item' is the wished item, return it
			return(item->GetData());
	};

	return NULL;	// If there are no enought items, return null
}

unsigned int List::Length()
// Get the lenght of the list
{
	unsigned int len = 0;

	ListEntry* aux = head_;
	while(aux)
	{
		if(aux->GetData())	// Only count entries with data
			len++;			// Maybe I should name it different?
		aux = aux->GetSig();
	};

	return len;
}

List::List():
	head_(NULL)
{}

List::~List()
{
	Reset();
}
