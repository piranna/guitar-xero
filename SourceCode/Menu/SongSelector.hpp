#ifndef SongSelector_hpp
#define SongSelector_hpp

#include "MenuData.hpp"


class SongSelector: public MenuData
{
private:
	char songPath_[256];

	void SetSongsDir(char* songPath);

	void Render();

	void ActionBack();
	void ActionExec(int index);

	void SetIndex(int index);
	void ShowSongInfo(char* songPath);
	void ShowAlbumInfo(char* albumPath);

	void ExecSong(char* path);

public:
	SongSelector( char* songPath);
};

#endif
