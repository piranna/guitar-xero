//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "SongSelector.hpp"

#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include "MenuAlbum.hpp"
#include "MenuSong.hpp"

#include "ParserOptions.hpp"
#include "common.hpp"
#include "constants.hpp"

#include "TextMenuManager.hpp"
#include "StartingMenu.hpp"
#include "SelectDificulty.hpp"
#include "NoSongs.hpp"

#include "MainLoop.hpp"
#include "PlaySong.hpp"

#include "MainMenu.hpp"

#include "Song.hpp"

#include "error.h"


void SongSelector::SetSongsDir(char* songPath)
{
	strcpy(songPath_, songPath);
	Render();
	SetIndex(0);
}

void SongSelector::Render()
{
	host_->Reset();

	char aux[256];
	GetFileExtension(aux, songPath_, "cover");
	((MainMenu*)MainLoop::mainLoop_->GetWindow())
		->SetAnimatedBackground(aux);

	DIR* pdir = opendir(songPath_);
	struct dirent* pent;

	while(pent=readdir(pdir))	// elements in directory
	{
		char path[256];
		sprintf(path, "%s/%s", songPath_, (char*)pent->d_name);

		struct stat entry;

		if((stat(path, &entry)!=-1)						// If path
			&& ((entry.st_mode & S_IFMT) == S_IFDIR)	// is a directory
			&& (strcmp((char*)pent->d_name, ".")!= 0)	// diferent of '.'
			&& (strcmp((char*)pent->d_name, "..")!= 0))	// or '..'
		{
//			char aux[256];
			sprintf(aux, "%s/%s", path, "song.ini");
			if(stat(aux, &entry)!=-1					// If the folder
				&& (entry.st_mode & S_IFMT)==S_IFREG)	// contains a song
			{
				ParserOptions parser(aux);		// If song is NOT tutorial
				parser.Read();					// add it to menu list

				if(strcmp(parser.GetConfig("song", "tutorial"),"1")!=0)
					host_->Append(new MenuSong(path));
			}
			else	// the folder contains an album... or not ;-)
			{
				// [TO-DO] include recursive folder code here

				host_->Append(new MenuAlbum(path));
			};
		};
	};
	closedir(pdir);

	if(!host_->GetLength())	// there are no songs/albums in library
	{
		host_->SetMenuManager(new TextMenuManager());
		host_->SetMenuData(new NoSongs());
	}
}


void SongSelector::ActionBack()
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	if(strcmp(songPath_,
		parser.GetConfig("game", "songs_root", SONGS_ROOT))!=0)
			// anti-xploit system
	{		// it was able to browse ALL computer files before this!!
//		video->SetFloatingBackground("");

		int pos=0;		// Look for the last one '/' to cut the songpath
		int index=0;
		while(songPath_[index]!='\0')
		{
			if(songPath_[index]=='/')
				pos=index;
			index++;
		};

		songPath_[pos]='\0';
		SetSongsDir(songPath_);
	}
	else	// same as BACK - Frets on Fire feature ;-)
	{
		host_->SetMenuManager(new TextMenuManager());
		host_->SetMenuData(new StartingMenu());
	}
}

void SongSelector::ActionExec(int index)
{
	if(Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(LESS, false);
		ActionBack();
	}

	else
	{
		MenuDirElement* item = (MenuDirElement*)host_->Get(index);

		if(item)
		{
			if(item->IsSong())
				ExecSong(item->GetPath());
			else
				SetSongsDir(item->GetPath());
		}
	}
}

void SongSelector::SetIndex(int index)
{
	MenuDirElement* item = (MenuDirElement*)host_->Get(index);

	if(item)
		if(item->IsSong())
		{
			char path[256];
			sprintf(path, "%s/%s", item->GetPath(), "song.ogg");
			Audio::audio_->LoadMusic(path);
			Audio::audio_->PlayMusic(-1);

			ShowSongInfo(item->GetPath());
		}
		else
			ShowAlbumInfo(item->GetPath());
}

void SongSelector::ShowSongInfo(char* songPath)
{
	// Load song.ini
	char aux[256];
	sprintf(aux, "%s/%s", songPath, "song.ini");
	ParserOptions parser(aux);
	parser.Read();

	parser.GetConfig("song", "artist");
	parser.GetConfig("song", "name");

// [TO-DO] Finish function
}

void SongSelector::ShowAlbumInfo(char* albumPath)
{
	DIR* pdir = opendir(albumPath);
	struct dirent* pent;

	int numSongs=0;
	int numAlbums=0;

	while(pent=readdir(pdir))	// elements in directory
	{
		char path[256];
		sprintf(path, "%s/%s", albumPath, (char*)pent->d_name);

		struct stat entry;

		if((stat(path, &entry)!=-1)						// If path
			&& ((entry.st_mode & S_IFMT) == S_IFDIR)	// is a directory
			&& (strcmp((char*)pent->d_name, ".")!= 0)	// diferent of '.'
			&& (strcmp((char*)pent->d_name, "..")!= 0))	// or '..'
		{
			char aux[256];
			sprintf(aux, "%s/%s", path, "song.ini");
			if(stat(aux, &entry)!=-1					// If the folder
				&& (entry.st_mode & S_IFMT)==S_IFREG)	// contains a song
			{
				ParserOptions parser(aux);		// If song is NOT tutorial
				parser.Read();					// add it

				if(strcmp(parser.GetConfig("song", "tutorial"),"1")!=0)
					numSongs++;
			}
			else	// the folder contains an album... or not ;-)
			{
				// [TO-DO] include recursive folder code here

				numAlbums++;
			};
		}
	};
	closedir(pdir);

// [TO-DO] Finish function
}

void SongSelector::ExecSong(char* path)
{
	Song* song = new Song(path);
	bool tracks[enumDificulty];

	switch(song->GetDificulties(tracks))
	{
		case 0:		// no dificulties
			{
				delete(song);
				WARNING("There are no tracks in the MIDI file");
			}
			break;
		case 1:		// dificulties = 1
			{
				int i=0;
				while(!(tracks[i]))
					i++;
				song->ParseMidi((tDificulty)i);

				MainLoop::mainLoop_->SetWindow(
									new PlaySong( song));
			}
			break;

		default:	// dificulties > 1
		{
			host_->SetMenuManager(new TextMenuManager());
			host_->SetMenuData(new SelectDificulty( song,
												tracks));
		}
	}
}


SongSelector::SongSelector( char* songPath):
	MenuData()
{
	strcpy(songPath_, songPath);

//	menu_->SetFont("JustMeAgainDownHere.ttf", 36);

//	char path[256];
//	GetFileExtension(path, MEDIA_DIR, "elvis_lapelvis");
//	video->SetBackground(path);

//	video->SetFloatingBackground("");
//	video->SetAnimator(new FadeIn(-300000, 60, 1));
}
