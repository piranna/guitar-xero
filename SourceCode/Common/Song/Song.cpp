//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "Song.hpp"

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "error.h"


void Song::AddNote(tAction cord, float start, float finish)
// Add a note in a cord setting its start and finish times
// and increment the number of notes registered in the dificulty
{
	if(notes_[cord])
	{
		Note* note = notes_[cord];
		while(note->GetSig())
			note = note->GetSig();

		note->SetSig(new Note(start, finish));
	}
	else
		notes_[cord] = new Note(start, finish);

	dificultyNumNotes_++;
}

void Song::RemoveNote(tAction note)
// Delete the first note in a cord, if any
{
	Note* aux = GetNote(note);
	if(aux)
	{
		notes_[note] = aux->GetSig();
		delete(aux);
	};
}

void Song::RemoveNotes()
// Remove all notes from the chords
{
	for(int x=FRET_1; x<=FRET_5; x++)
		while(notes_[x])
			RemoveNote((tAction)x);
}

void Song::Play()
// Start to play the song from the begining
{
	Audio::audio_->PlayMusic(0);
	Audio::audio_->PlayGuitar();
}

void Song::Stop()
// Stop the song
{
	Audio::audio_->StopMusic();
	Audio::audio_->StopGuitar();
}

void Song::Pause()
// Pause the song
{
	Audio::audio_->PauseMusic();
	Audio::audio_->PauseGuitar();
}

void Song::Resume()
// Resume the song if it was paused
{
	Audio::audio_->ResumeMusic();
	Audio::audio_->ResumeGuitar();
}

void Song::Reset()
// Reset the song, reloading it
// and reparsing the notes for the current dificulty
{
	Stop();
	LoadSong();
	ParseMidi(dificulty_);
}

void Song::LoadSong()
// Load the song
{
	// Load song music and guitar
	Audio::audio_->LoadSong(songPath_);

	// Set number of parsings to 0
	count_ = 0;

	// Delete old midifile, if any
	if(midifile_)
		delete(midifile_);

	// Create new midifile
	char path[256];
	sprintf(path, "%s/%s", songPath_, "notes.mid");
	midifile_ = new MidiFile(path);

	// Parse script if configured
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();
	if(strcmp(parser.GetConfig("game", "subtitles"), "True")==0)
	{
		while(script_)
		{
			ScriptEntry* aux = script_;
			script_ = script_->sig_;
			delete(aux);
		}

		sprintf(path, "%s/%s", songPath_, "script.txt");
		ParserScript parser(path);
		parser.Read();
		script_ = parser.GetSubtitles();
	};
}

void Song::SetTempo(int index)
{
	_MFEvent& mididata = midifile_->getEvent(0, index);

	int microseconds = 0;
	microseconds = microseconds | (mididata.data[3] << 16);
	microseconds = microseconds | (mididata.data[4] << 8);
	microseconds = microseconds | (mididata.data[5] << 0);

	double newtempo = 60.0 / microseconds * 1000000.0;
	count_++;

	if(count_ <= 1)
		bpm_ = newtempo;
	else if (bpm_ != newtempo)
		cout << "; WARNING: change of BPM from " << bpm_
			<< " to " << newtempo << " ignored" << endl;
}

int Song::GetDificulties(bool tracks[enumDificulty])
// Get dificulties availables for the song,
// store them in tracks[]
// return its number
{
	int numLevels=0;

	// Init tracks[]
	for(int track=0; track<enumDificulty; track++)
		tracks[(tDificulty)track]=false;

	midifile_->joinTracks();

	// Get midi events, identify them for the correct dificulty
	// and set it as an available dificulty
	for(int i=0; i<midifile_->getNumEvents(0)
				&& numLevels<enumDificulty; i++)
	{
		int command = midifile_->getEvent(0, i).data[0] & 0xf0;
		if (command == 0x90 || command == 0x80)
		{
			switch(midifile_->getEvent(0, i).data[1])
			{
				case 60: case 61: case 62: case 63: case 64:
					if(!(tracks[SUPAEASY]))
					{
						tracks[SUPAEASY]=true;
						numLevels++;
					};
					break;
				case 72: case 73: case 74: case 75: case 76:
					if(!(tracks[EASY]))
					{
						tracks[EASY]=true;
						numLevels++;
					};
					break;
				case 84: case 85: case 86: case 87: case 88:
					if(!(tracks[MEDIUM]))
					{
						tracks[MEDIUM]=true;
						numLevels++;
					};
					break;
				case 96: case 97: case 98: case 99: case 100:
					if(!(tracks[AMAZING]))
					{
						tracks[AMAZING]=true;
						numLevels++;
					};
					break;
				default:
					cout << "WARNING: incorrect level identificator\n";
			};
		};
	};

	// Return number of dificulties
	return numLevels;
}

int Song::GetDificultyNumNotes()
// Get number of notes in selected dificulty
{
	return dificultyNumNotes_;

//	midifile_->joinTracks();
//	return midifile_->getNumEvents(0);
}

void Song::ParseMidi(tDificulty dificulty)
// Parse midifile for the selected dificulty to a notes list
// and set the number of notes for it
{
	RemoveNotes();

	dificulty_ = dificulty;
	dificultyNumNotes_ = 0;

	midifile_->absoluteTime();
	midifile_->joinTracks();

	Array<double> ontimes(128);
	for(int i=0; i<128; i++)
		ontimes[i] = -1.0;
//printf("antes: %f\n", bpm_);
	bpm_ = 60.0;
//printf("durante: %f\n", bpm_);

	for (int i=0; i<midifile_->getNumEvents(0); i++)
	{
		int command = midifile_->getEvent(0, i).data[0] & 0xf0;
		if (command == 0x90 && midifile_->getEvent(0, i).data[2] != 0)
		{
			// store note-on velocity and time
			int key = midifile_->getEvent(0, i).data[1];
			ontimes[key] = midifile_->getEvent(0, i).time * 60.0 / bpm_ / 
							midifile_->getTicksPerQuarterNote();
		}
		else if (command == 0x90 || command == 0x80)
		{
			// note off command write to output
			int key = midifile_->getEvent(0, i).data[1];
			double offtime = midifile_->getEvent(0, i).time * 60.0 /
						midifile_->getTicksPerQuarterNote() / bpm_;
//			cout << "note\t" << ontimes[key] 
//				<< "\t" << offtime - ontimes[key]
//				<< "\t" << key << "\t" << endl;

//			switch(dificulty)
//			{
//				case SUPAEASY:	baseKey = 60;	break;
//				case EASY:		baseKey = 72;	break;
//				case MEDIUM:	baseKey = 84;	break;
//				case AMAZING:	baseKey = 96;	break;
//			}
//
//			if(((baseKey-key) >=0) && ((baseKey-key) <5))
//				AddNote(baseKey-key, ontimes[key], offtime);

			switch(dificulty)
			{
				case SUPAEASY:
					switch(key)
					{
						case 60:
							AddNote(FRET_1, ontimes[key], offtime);
							break;
						case 61:
							AddNote(FRET_2, ontimes[key], offtime);
							break;
						case 62:
							AddNote(FRET_3, ontimes[key], offtime);
							break;
						case 63:
							AddNote(FRET_4, ontimes[key], offtime);
							break;
						case 64:
							AddNote(FRET_5, ontimes[key], offtime);
							break;
					};
					break;
				case EASY:
					switch(key)
					{
						case 72:
							AddNote(FRET_1, ontimes[key], offtime);
							break;
						case 73:
							AddNote(FRET_2, ontimes[key], offtime);
							break;
						case 74:
							AddNote(FRET_3, ontimes[key], offtime);
							break;
						case 75:
							AddNote(FRET_4, ontimes[key], offtime);
							break;
						case 76:
							AddNote(FRET_5, ontimes[key], offtime);
							break;
					};
					break;
				case MEDIUM:
					switch(key)
					{
						case 84:
							AddNote(FRET_1, ontimes[key], offtime);
							break;
						case 85:
							AddNote(FRET_2, ontimes[key], offtime);
							break;
						case 86:
							AddNote(FRET_3, ontimes[key], offtime);
							break;
						case 87:
							AddNote(FRET_4, ontimes[key], offtime);
							break;
						case 88:
							AddNote(FRET_5, ontimes[key], offtime);
							break;
					};
					break;
				case AMAZING:
					switch(key)
					{
						case 96:
							AddNote(FRET_1, ontimes[key], offtime);
							break;
						case 97:
							AddNote(FRET_2, ontimes[key], offtime);
							break;
						case 98:
							AddNote(FRET_3, ontimes[key], offtime);
							break;
						case 99:
							AddNote(FRET_4, ontimes[key], offtime);
							break;
						case 100:
							AddNote(FRET_5, ontimes[key], offtime);
							break;
					};
					break;
			};

			ontimes[key] = -1.0;
		} 

		// check for tempo indication
		if (midifile_->getEvent(0, i).data[0] == 0xff &&
								midifile_->getEvent(0, i).data[1] == 0x51)
			SetTempo(i);
	}
//printf("despues: %f\n", bpm_);
}

void Song::ParseMidi(char* dificulty)
// Get dificulty and parse midifile
{
	switch(atoi(dificulty))
	{
		case 0:
			ParseMidi(SUPAEASY);
			break;
		case 1:
			ParseMidi(EASY);
			break;
		case 2:
			ParseMidi(MEDIUM);
			break;
		case 3:
			ParseMidi(AMAZING);
			break;
		default:
			ERROR("ParseMidi(" << dificulty << ") failed");
	};
}

Song::Song(char* songPath):
//	info_=SongInfo(songPath);
//	playing_=false;
//	start_=0.0;
//	noteFileName_=

	midifile_(NULL),
	dificulty_(SUPAEASY),
	dificultyNumNotes_(0),
	bpm_(60.0),
	script_(NULL)
{
	for(int x=FRET_1; x<=FRET_5; x++)
		notes_[x]=NULL;

	strlcpy(songPath_, songPath, 256);
	LoadSong();
}

Song::~Song()
{
	Stop();

	delete(midifile_);

	while(script_)
	{
		ScriptEntry* aux = script_;
		script_ = script_->sig_;
		delete(aux);
	}

	RemoveNotes();
}
