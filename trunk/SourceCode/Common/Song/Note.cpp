//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Note.hpp"

#include <stdlib.h>


// Note
bool Note::IsActive()
// Get if the note is active
{
	return active_;
}

bool Note::IsLong()
// Get if it is a long note
{
	return (finish_-star_);
}

bool Note::IsStar()
// Get if it is a star note
{
	return star_;
}

void Note::SetInactive()
// Set note inactive
{
	active_=false;
}

float Note::GetStart()
// Get note start
{
	return start_;
}

float Note::GetFinish()
// Get note finish
{
	return finish_;
}

void Note::SetSig(Note* sig)
// Set the next note
{
	sig_ = sig;
}

Note* Note::GetSig()
// Get the next note
{
	return sig_;
}


Note::Note(float start, float finish):
	active_(true),
	start_(start),
	finish_(finish),
	sig_(NULL),
	star_(false)
{}


// NoteStar
NoteStar::NoteStar(float start, float finish):
	Note(start, finish)
{
	star_=true;
}