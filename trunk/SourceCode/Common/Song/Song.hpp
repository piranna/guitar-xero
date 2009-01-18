//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef __CLSSONG_HPP__
#define __CLSSONG_HPP__

#include "Note.hpp"
#include "Actions.hpp"

#include "Audio.hpp"
#include "ParserScript.hpp"

#include "MidiFile.h"


enum tDificulty {SUPAEASY, EASY, MEDIUM, AMAZING, enumDificulty};


class Song
{
private:
//	info_;
//	boolean playing_;
//	float start_;
//	noteFileName_;

	MidiFile* midifile_;
	tDificulty dificulty_;
	float bpm_;
	Note* notes_[FRET_5+1];
	int dificultyNumNotes_;

	char songPath_[256];

	void SetTempo(int index);
	int count_;

	void LoadSong();

public:
	ScriptEntry* script_;

	float GetBpm(){return bpm_;};
	Note* GetNote(tAction note){return notes_[note];};
	void AddNote(tAction cord, float start, float finish);
	void RemoveNote(tAction note);
	void RemoveNotes();

	int GetDificulties(bool tracks[enumDificulty+1]);
	int GetDificultyNumNotes();
	void ParseMidi(tDificulty dificulty);
	void ParseMidi(char* dificulty);

	void Play();
	void Stop();
	void Pause();
	void Resume();
	void Reset();
//	void SetGuitarVolume(volume);
//	void SetRhythmVolume(volume);
//	void SetBackgroundVolume(volume);
//	void FadeOut(time);
//	float GetPosition();
//	bool IsPlaying();
//	float GetBeat();
//	GetTrack();
	ScriptEntry* GetScript(){return script_;};
	char* GetSongPath(){return songPath_;};

	Song(char* songPath);
	~Song();
};

#endif
