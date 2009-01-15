#ifndef PlaySong_hpp
#define PlaySong_hpp

#include "WidgetWindow.hpp"

#include "Timer.hpp"
#include "Song.hpp"
#include "constants.hpp"

#include "WidgetFretboard.hpp"
#include "WidgetLifebar.hpp"
#include "WidgetScript.hpp"
#include "WidgetSplash.hpp"

#include "WidgetWindow.hpp"


class PlaySong: public WidgetWindow
{
private:

	Song* song_;

	WidgetFretboard* fretBoard_;
	WidgetLifebar* lifeBar_;
	WidgetScript* script_;
	WidgetSplash* finalSplash_;
	WidgetWindow* pauseWindow_;
	bool closePauseWindow_;

	bool notePushed_[FRET_5+1];
	bool longNoteActive_[FRET_5+1];
	float energy_;
	float volumeGuitar_;

	void ProcessActions();
	void KeepPlayingGuitar();
	void CheckNotes();
	void ExecVibratto();
	void MoveSong();

	void PlayFailure(char* sound);
	void SilenceGuitar();

	void Pause();
	void Resume();

	void InitialDelay();

public:
	Song* GetSong();

	void ResetSong();
	void ClosePauseWindow();

	PlaySong(Song* song);
	~PlaySong();
};

#endif
