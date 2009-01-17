#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

const int MAX_SONGS = 1000;
const int SELECT_SONG_SCROLL_SPEED = 10;
const int BUTTONS_LINE = 432;

const unsigned char NUM_FRETS = 5;

const float SECONDS_NOTE_WINDOW = 0.25;
const int POINTS_PER_NOTE = 50;
const int POINTS_PER_SECOND = 100;

const float INTENSITY_UNFOCUSED = 0.5;

const int SLIDER_WIDTH = 100;

#ifdef __APPLE__
	//const char* MEDIA_DIR = "Guitar Xero.app/Contents/Resources/Media";
	#define MEDIA_DIR		"Guitar Xero.app/Contents/Resources/Media"
	#define LANGUAGES_PATH	"Guitar Xero.app/Contents/Resources/Languages"
	#define MODS_PATH		"Guitar Xero.app/Contents/Resources/Mods"
	#define SONGS_ROOT		"Guitar Xero.app/Contents/Resources/Songs"
	#define TUTORIAL_PATH	"Guitar Xero.app/Contents/Resources/Tutorial"

	#define GUITARXERO_INI	"Guitar Xero.app/Contents/Resources/GuitarXero.ini"
#else
	//const char* MEDIA_DIR = "Resources/Media";
	#define MEDIA_DIR		"Resources/Media"
	#define LANGUAGES_PATH	"Resources/Languages"
	#define MODS_PATH		"Resources/Mods"
	#define SONGS_ROOT		"Resources/Songs"
	#define TUTORIAL_PATH	"Resources/Tutorial"

	#define GUITARXERO_INI	"Resources/GuitarXero.ini"
#endif

#endif
