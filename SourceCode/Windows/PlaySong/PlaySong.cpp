//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "PlaySong.hpp"

#include "Video.hpp"

#include "ParserOptions.hpp"

#include "MainLoop.hpp"
#include "SongFinished.hpp"

#include "WidgetBackground.hpp"
#include "PauseWindow.hpp"

#include "defaults.h"

#include "GX_Common.hpp"


void PlaySong::ClosePauseWindow()
{
	closePauseWindow_ = true;
}

void PlaySong::ProcessActions()
{
	if(pauseWindow_)
	{
		pauseWindow_->ProcessActions();
		if(closePauseWindow_)
		{
			RemoveLastWidget();
			pauseWindow_ = NULL;
			closePauseWindow_ = false;
			Resume();
		}
	}
	else
	{
		// Pause menu
		if(Actions::actions_->GetAction(BACK))
		{
			Actions::actions_->SetAction(BACK, false);

			Pause();
			pauseWindow_ = new PauseWindow( this);
			AppendWidget(pauseWindow_);

//			pauseWindow_ = WidgetWindow::Make(50, 50,
//								new PauseWindow( this));
		}
		else
		{
			// Frets
			for(int i=FRET_1; i<=FRET_5; i++)
			{
				// User has presed fret
				if(Actions::actions_->GetAction((tAction)i))
				{
					if(longNoteActive_[(tAction)i])
						lifeBar_->AddPoints(Timer::timer_->GetDiffTime());
				}

				// User has release fret and long note is active
				else if(longNoteActive_[(tAction)i])
				{
					longNoteActive_[(tAction)i]=false;

					KeepPlayingGuitar();
				};
			};

			// Pick
			if(Actions::actions_->GetAction(PICK))
			{
				Actions::actions_->SetAction(PICK, false);

				CheckNotes();
			};

			// Tilt
			if(Actions::actions_->GetAction(TILT))
			{
				Actions::actions_->SetAction(TILT, false);

				if(energy_>=50.0)
				{
				
				};
			};

			// Vibratto
			if(Actions::actions_->GetAction(VIBRATTO))
			{
				Actions::actions_->SetAction(VIBRATTO, false);

				for(int i=FRET_1; i<=FRET_5; i++)
					if(longNoteActive_[(tAction)i])
					{
						ExecVibratto();
						break;
					}
			}
//			else
//				Audio::audio_->VolumeGuitar(volumeGuitar_);

			MoveSong();
		};
	};
}

void PlaySong::KeepPlayingGuitar()
{
	bool keepPlayingGuitar = false;
	for(int i=FRET_1; i<=FRET_5; i++)
		if(longNoteActive_[(tAction)i])
		{
			keepPlayingGuitar = true;
			continue;
		};

	if(!keepPlayingGuitar)
		SilenceGuitar();
}

void PlaySong::PlayFailure(char* sound)
{
	char aux[256];
	GetRandomFile(aux, MEDIA_DIR, sound);
	Audio::audio_->PlayFailure(aux);

	lifeBar_->ResetHits();
	SilenceGuitar();
}

void PlaySong::SilenceGuitar()
{
	for(int i=0; i<NUM_FRETS; i++)
		longNoteActive_[i] = false;

	Audio::audio_->VolumeGuitar(0);
}

void PlaySong::Pause()
{
	song_->Pause();
	Timer::timer_->PauseSong();
}

void PlaySong::Resume()
{
	if(Audio::audio_->GetState()==PLAYING)
		song_->Resume();
	Timer::timer_->ResumeSong();
}

void PlaySong::CheckNotes()
{
	bool pickNote=false;

	// Get active (and playable) notes
	Note* note[NUM_FRETS];
	for(int i=0; i<NUM_FRETS; i++)
	{
		note[i] = song_->GetNote((tAction)i);
		while(note[i] && !(note[i]->IsActive()))	// Looking for first
			note[i]=note[i]->GetSig();			// active note in cord list

		if(note[i]
			&& (note[i]->GetStart()-SECONDS_NOTE_WINDOW	// There is a note
				<= Timer::timer_->GetSongTime()))
		{
			if(note[i]->GetStart()+SECONDS_NOTE_WINDOW	// It's a pick note
						>= Timer::timer_->GetSongTime())
				pickNote=true;
		}
		else	// It's not a (playable) note
			note[i]=NULL;
	}

	// There is at least one fret to pick
	if(pickNote)
	{
		// Check if all chords are correctly picked
		int correctNotes = 0;
		for(int i=FRET_1; i<=FRET_5; i++)
		{
			if(Actions::actions_->GetAction((tAction)i))	// Chord picked
			{
				if(note[i])					// Chord correctly picked
					correctNotes++;
				else						// User has pick a wrong chord
				{
					PlayFailure("fiba");
					break;
				}
			}
			else if(!note[i])			// Not pushed chord AND not note
				correctNotes++;
		}

		// If all chords are correctly picked, active them and add points
		if(correctNotes==NUM_FRETS)
		{
			for(int i=0; i<NUM_FRETS; i++)
				if(note[i]							// It's a pick note
					&& note[i]->GetStart()+SECONDS_NOTE_WINDOW
						>= Timer::timer_->GetSongTime())
				{
					if(note[i]->IsStar())
					{
						// [TO-DO] Add Star notes code (check vibratto)
					};

					notePushed_[i] = true;
					longNoteActive_[i] = note[i]->IsLong();

					lifeBar_->AddHit();
				}
			Audio::audio_->VolumeGuitar(volumeGuitar_);
		}
	}
	else	// There are NO frets to pick
		PlayFailure("crunch");
}

void PlaySong::ExecVibratto()
{
	Audio::audio_->VolumeGuitar(volumeGuitar_*0.75);
}

Song* PlaySong::GetSong()
{
	return song_;
}

void PlaySong::ResetSong()
{
	song_->Reset();
	InitialDelay();
}

void PlaySong::MoveSong()
{
	switch(Audio::GetState())
	{
		case PLAYING:
			for(int i=FRET_1; i<=FRET_5; i++)
			{
				Note* note = song_->GetNote((tAction)i);
				if(note)
				{
					// Note finished
					if(note->GetFinish() < Timer::timer_->GetSongTime())
					{
						song_->RemoveNote((tAction)i);
						notePushed_[(tAction)i]=false;
						longNoteActive_[(tAction)i]=false;
					}

					// Note not pushed
					else if((note->GetStart()+SECONDS_NOTE_WINDOW
							< Timer::timer_->GetSongTime())
							&& !notePushed_[(tAction)i])
					{
						lifeBar_->ResetHits();
						note->SetInactive();
						KeepPlayingGuitar();
					};
				};
			};

			if(script_)
				script_->Move();
			break;

		case PAUSED:
			if(Timer::timer_->GetSongTime()>=0.0)
				song_->Resume();
			break;

		case STOPPED:
			if(!finalSplash_)
			{
				finalSplash_ = new WidgetSplash(
								GX_Graphic::Make("It Rocks!", MEDIA_DIR, "laundromat_1967.ttf", 60,
								Char2tColor(LoadTheme("base_color",
														BASE_COLOR))));
				AppendWidget(finalSplash_);
			}
			if(!finalSplash_ || finalSplash_->GetTime() > 2.0)
			{
				MainLoop::mainLoop_->SetWindow(
							new SongFinished(
								lifeBar_->GetPoints(),
								lifeBar_->GetHits()
									/(float)song_->GetDificultyNumNotes(),
								lifeBar_->GetMaxHits()));
			}
			break;
	}
}

void PlaySong::InitialDelay()
{
	song_->Play();						// Start song
	song_->Pause();						// Pause song for initial delay
	Timer::timer_->InitSongTime(-3);	// Init timer with a delay
}


PlaySong::PlaySong(Song* song):
	song_(song),
	fretBoard_(new WidgetFretboard(song)),
	lifeBar_(new WidgetLifebar()),
	script_(new WidgetScript(song->script_)),
	finalSplash_(NULL),
	pauseWindow_(NULL),
	closePauseWindow_(false),
	energy_(0.0),
	volumeGuitar_(1.0)
{
	char path[256];
	GetFileExtension(path, MEDIA_DIR, "elvis_lapelvis");
	AppendWidget(new WidgetBackground(path));

	sprintf(path, "%s/neck.png", MEDIA_DIR);
	fretBoard_->SetFretImage(path);

	// Single user
	// Dual user = (0,0) and (width,0)
	fretBoard_->SetPos(200, 0);
	AppendWidget(fretBoard_);

	AppendWidget(lifeBar_);
	AppendWidget(script_);

	for(int i=FRET_1; i<=FRET_5; i++)
	{
		notePushed_[(tAction)i]=false;
		longNoteActive_[(tAction)i]=false;
	};

	ParserOptions parser(GUITARXERO_INI);
	parser.Read();
	volumeGuitar_= atof(parser.GetConfig("audio", "guitarvol", "1.0"));

	InitialDelay();
}

PlaySong::~PlaySong()
{
	delete(song_);
	delete(fretBoard_);
	delete(lifeBar_);
	delete(script_);
	delete(pauseWindow_);
}
