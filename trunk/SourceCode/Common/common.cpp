//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "common.hpp"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "ParserOptions.hpp"
#include "constants.hpp"

#include "compileConfiguration.h"

#include "error.h"


//void Append(char* cadena, char caracter, int lenght)
void Append(char* cadena, char caracter)
// Add a characted to the end of a string
{
	char* auxCadena=cadena;

	// Search end of cadena
	while(*auxCadena!='\0')
		auxCadena++;

	// Put caracter and null character at end of cadena
	*auxCadena=caracter;
	*(auxCadena+1)='\0';
}

void Unhead(char* cadena, int cut)
// Delete 'cut' characters from the 'cadena' head
{
	if(cut)
	{
		char* auxCadena=cadena;

		// Copy characters to cadena head
		while(*(auxCadena+cut)!='\0')
		{
			*auxCadena=*(auxCadena+cut);
			auxCadena++;
		};

		// Put null character
		*auxCadena='\0';
	}
}

void Untail(char* cadena, int cut)
// Delete 'cut' characters from the 'cadena' tail
{
	char* auxCadena=cadena;

	// Search end of cadena
	while(*auxCadena!='\0')
		auxCadena++;

	// Put null character at cut position
	*(auxCadena-cut)='\0';
}

void Unspace(char* cadena)
// Erase all spaces and tabs from the head and tail of the string
{
	char* auxCadena=cadena;

	// Erase cadena head spaces and tabs using the diference
	// between the first non-space character mem position
	// and 'cadena' head mem position
	while((*auxCadena==' ') || (*auxCadena=='\t'))
		auxCadena++;
	Unhead(cadena, auxCadena-cadena);

	// Search end of cadena
	while(*auxCadena!='\0')
		auxCadena++;

	// Put a null character in 'cadena'
	// so all tail spaces and tabs are left out
	do
	{
		auxCadena--;
	} while((*auxCadena==' ') || (*auxCadena=='\t'));
	*(auxCadena+1)='\0';
}

char* GetText(char* original)
// Get the translation of 'original' in the current language
{
	// Get language from config file
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();
	char language[32];
	strcpy(language, parser.GetConfig("game", "language"));

	// If language is not defined or is "English" (default)
	// return original string
	if(strcmp(language,"language")==0 || strcmp(language,"English")==0)
		return original;

	// Load language file
	char path[256];
	sprintf(path, "%s/%s.lang", LANGUAGES_PATH, language);
	parser.SetFile(path);
	parser.Read();

	// Return translated string
	return parser.GetConfig(language, original);
}

void GetFileExtension(char* path, char* albumPath, char* fileName)
// Search in 'dirPath' for a file with a base name == 'fileName'
// and set 'path' to the full path of the file with its file extension
{
	// Default if there's no file
	strcpy(path, "");

	// Open directory
	DIR* pdir = opendir(albumPath);
	struct dirent* pent;

	// Loop over all elements in directory
	while(pent=readdir(pdir))
		// If selected file basename == 'fileName',
		// set file full path and end loop
		if(strncmp((char*)pent->d_name, fileName, strlen(fileName))==0)
		{
			sprintf(path, "%s/%s", albumPath, (char*)pent->d_name);
			break;
		};

	// Close directory
	closedir(pdir);
}

void GetRandomFile(char* path, char* dirPath, char* fileName)
// Search in 'dirPath' for files with a base name == 'fileName'
// and set 'path' to the full path of one random file of them
// with its file extension.
// Files must be in the form basename#.extension,
// being # correlative integer numbers since 1.
{
	int copies = 0;

	// Get number of copies in directory
	DIR* pdir = opendir(dirPath);
	struct dirent* pent;

	while(pent=readdir(pdir))	// elements in directory
		if(strncmp((char*)pent->d_name, fileName, strlen(fileName))==0)
			copies++;

	closedir(pdir);

	// Set full base name of the file (basename + number)
	char aux[32];
	sprintf(aux, "%s%i", fileName,
						1 + int(copies * (rand()/(double)RAND_MAX)));

	// Get full path of file
	GetFileExtension(path, dirPath, aux);
}

tColor* LoadButtonsColors()
// Load buttons colors definitions from config file
{
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	// Create a new buttons colors array and init it
	tColor* fretColor = new tColor[5];
	for(int i=0; i<5; i++)
	{
		// Compose button color name
		char fretName[12];
		sprintf(fretName, "fret%i_color", i);

		// Get button color
		fretColor[i] = Char2tColor(LoadTheme(fretName,
											GetDefaultButtonColor(i)));
	};

	// Return buttons colors
	return fretColor;
}

tColor Char2tColor(char* car)
// Get a tColor from a color defined in a string in a hexadecimal form
{
	unsigned int color;
	sscanf(car, "#%x", &color);

	tColor out;
	out.r = color / 65536;
	out.g = (color % 65536)/256;
	out.b = color % 256;

	return out;
}

char* GetDefaultButtonColor(int num)
// Get default button colors
{
	switch(num)
	{
		case 0:	return "#22FF22";
		case 1:	return "#FF2222";
		case 2:	return "#FFFF22";
		case 3:	return "#3333FF";
		case 4:	return "#FF22FF";
	};

	return NULL;
}

char* LoadTheme(char* option, char* def)
// Load a theme option.
// This is diferent from "traditionals" GetConfigs and GetOptions
// since we may need to read several mod files (others that config file)
// and apply its values from there if they are active
{
	// Open config file for user defined theme options
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	// Open mods dir
	DIR* pdir = opendir(MODS_PATH);
	struct dirent* pent;

	// Read all mods in directory
	while(pent=readdir(pdir))
		if((strcmp((char*)pent->d_name, ".")!= 0)
			&& (strcmp((char*)pent->d_name, "..")!= 0))
		{
			// Get mod name
			char ListEntry[32];
			sprintf(ListEntry, "mod_%s", (char*)pent->d_name);

			// If mod is active, get its config file
			// and add its data to the current config file in memory
			if(strcmp(parser.GetConfig("mods", ListEntry), "True")==0)
			{
				char pathMod[256];
				sprintf(pathMod, "%s/%s/%s", MODS_PATH,
						(char*)pent->d_name, "theme.ini");

				parser.SetFile(pathMod);
				parser.Merge();
			};
		};
	closedir(pdir);

	// Return config value
	return parser.GetConfig("theme", option, def);
}

char* KeyName2PyGameKey(char* keyName)
// Get a PyGameKey definition for a KeyName given (SDL KeyNames only?)
{
	if(strcmp(keyName, "backspace")==0)			return "K_BACKSPACE";
	if(strcmp(keyName, "tab")==0)				return "K_TAB";
	if(strcmp(keyName, "clear")==0)				return "K_CLEAR";
	if(strcmp(keyName, "return")==0)			return "K_RETURN";
	if(strcmp(keyName, "pause")==0)				return "K_PAUSE";
	if(strcmp(keyName, "escape")==0)			return "K_ESCAPE";
	if(strcmp(keyName, "space")==0)				return "K_SPACE";
	if(strcmp(keyName, "exclaim")==0)			return "K_EXCLAIM";
	if(strcmp(keyName, "quotedbl")==0)			return "K_QUOTEDBL";
	if(strcmp(keyName, "hash")==0)				return "K_HASH";
	if(strcmp(keyName, "dollar")==0)			return "K_DOLLAR";
	if(strcmp(keyName, "ampersand")==0)			return "K_AMPERSAND";
	if(strcmp(keyName, "quote")==0)				return "K_QUOTE";
	if(strcmp(keyName, "left parenthesis")==0)	return "K_LEFTPAREN";
	if(strcmp(keyName, "right parenthesis")==0)	return "K_RIGHTPAREN";
	if(strcmp(keyName, "asterisk")==0)			return "K_ASTERISK";
	if(strcmp(keyName, "plus sign")==0)			return "K_PLUS";
	if(strcmp(keyName, "comma")==0)				return "K_COMMA";
	if(strcmp(keyName, "minus sign")==0)		return "K_MINUS";
	if(strcmp(keyName, "period")==0)			return "K_PERIOD";
	if(strcmp(keyName, "forward slash")==0)		return "K_SLASH";
	if(strcmp(keyName, "0")==0)					return "K_0";
	if(strcmp(keyName, "1")==0)					return "K_1";
	if(strcmp(keyName, "2")==0)					return "K_2";
	if(strcmp(keyName, "3")==0)					return "K_3";
	if(strcmp(keyName, "4")==0)					return "K_4";
	if(strcmp(keyName, "5")==0)					return "K_5";
	if(strcmp(keyName, "6")==0)					return "K_6";
	if(strcmp(keyName, "7")==0)					return "K_7";
	if(strcmp(keyName, "8")==0)					return "K_8";
	if(strcmp(keyName, "9")==0)					return "K_9";
	if(strcmp(keyName, "colon")==0)				return "K_COLON";
	if(strcmp(keyName, "semicolon")==0)			return "K_SEMICOLON";
	if(strcmp(keyName, "less-than sign")==0)	return "K_LESS";
	if(strcmp(keyName, "equals sign")==0)		return "K_EQUALS";
	if(strcmp(keyName, "greater-than sign")==0)	return "K_GREATER";
	if(strcmp(keyName, "question mark")==0)		return "K_QUESTION";
	if(strcmp(keyName, "at")==0)				return "K_AT";
	if(strcmp(keyName, "left bracket")==0)		return "K_LEFTBRACKET";
	if(strcmp(keyName, "backslash")==0)			return "K_BACKSLASH";
	if(strcmp(keyName, "right bracket")==0)		return "K_RIGHTBRACKET";
	if(strcmp(keyName, "caret")==0)				return "K_CARET";
	if(strcmp(keyName, "underscore")==0)		return "K_UNDERSCORE";
	if(strcmp(keyName, "grave")==0)				return "K_BACKQUOTE";
	if(strcmp(keyName, "a")==0)					return "K_a";
	if(strcmp(keyName, "b")==0)					return "K_b";
	if(strcmp(keyName, "c")==0)					return "K_c";
	if(strcmp(keyName, "d")==0)					return "K_d";
	if(strcmp(keyName, "e")==0)					return "K_e";
	if(strcmp(keyName, "f")==0)					return "K_f";
	if(strcmp(keyName, "g")==0)					return "K_g";
	if(strcmp(keyName, "h")==0)					return "K_h";
	if(strcmp(keyName, "i")==0)					return "K_i";
	if(strcmp(keyName, "j")==0)					return "K_j";
	if(strcmp(keyName, "k")==0)					return "K_k";
	if(strcmp(keyName, "l")==0)					return "K_l";
	if(strcmp(keyName, "m")==0)					return "K_m";
	if(strcmp(keyName, "n")==0)					return "K_n";
	if(strcmp(keyName, "o")==0)					return "K_o";
	if(strcmp(keyName, "p")==0)					return "K_p";
	if(strcmp(keyName, "q")==0)					return "K_q";
	if(strcmp(keyName, "r")==0)					return "K_r";
	if(strcmp(keyName, "s")==0)					return "K_s";
	if(strcmp(keyName, "t")==0)					return "K_t";
	if(strcmp(keyName, "u")==0)					return "K_u";
	if(strcmp(keyName, "v")==0)					return "K_v";
	if(strcmp(keyName, "w")==0)					return "K_w";
	if(strcmp(keyName, "x")==0)					return "K_x";
	if(strcmp(keyName, "y")==0)					return "K_y";
	if(strcmp(keyName, "z")==0)					return "K_z";
	if(strcmp(keyName, "delete")==0)			return "K_DELETE";
	if(strcmp(keyName, "keypad 0")==0)			return "K_KP0";
	if(strcmp(keyName, "keypad 1")==0)			return "K_KP1";
	if(strcmp(keyName, "keypad 2")==0)			return "K_KP2";
	if(strcmp(keyName, "keypad 3")==0)			return "K_KP3";
	if(strcmp(keyName, "keypad 4")==0)			return "K_KP4";
	if(strcmp(keyName, "keypad 5")==0)			return "K_KP5";
	if(strcmp(keyName, "keypad 6")==0)			return "K_KP6";
	if(strcmp(keyName, "keypad 7")==0)			return "K_KP7";
	if(strcmp(keyName, "keypad 8")==0)			return "K_KP8";
	if(strcmp(keyName, "keypad 9")==0)			return "K_KP9";
	if(strcmp(keyName, "keypad period")==0)		return "K_KP_PERIOD";
	if(strcmp(keyName, "keypad divide")==0)		return "K_KP_DIVIDE";
	if(strcmp(keyName, "keypad multiply")==0)	return "K_KP_MULTIPLY";
	if(strcmp(keyName, "keypad minus")==0)		return "K_KP_MINUS";
	if(strcmp(keyName, "keypad plus")==0)		return "K_KP_PLUS";
	if(strcmp(keyName, "keypad enter")==0)		return "K_KP_ENTER";
	if(strcmp(keyName, "keypad equals")==0)		return "K_KP_EQUALS";
	if(strcmp(keyName, "up arrow")==0)			return "K_UP";
	if(strcmp(keyName, "down arrow")==0)		return "K_DOWN";
	if(strcmp(keyName, "right arrow")==0)		return "K_RIGHT";
	if(strcmp(keyName, "left arrow")==0)		return "K_LEFT";
	if(strcmp(keyName, "insert")==0)			return "K_INSERT";
	if(strcmp(keyName, "home")==0)				return "K_HOME";
	if(strcmp(keyName, "end")==0)				return "K_END";
	if(strcmp(keyName, "page up")==0)			return "K_PAGEUP";
	if(strcmp(keyName, "page down")==0)			return "K_PAGEDOWN";
	if(strcmp(keyName, "f1")==0)				return "K_F1";
	if(strcmp(keyName, "f2")==0)				return "K_F2";
	if(strcmp(keyName, "f3")==0)				return "K_F3";
	if(strcmp(keyName, "f4")==0)				return "K_F4";
	if(strcmp(keyName, "f5")==0)				return "K_F5";
	if(strcmp(keyName, "f6")==0)				return "K_F6";
	if(strcmp(keyName, "f7")==0)				return "K_F7";
	if(strcmp(keyName, "f8")==0)				return "K_F8";
	if(strcmp(keyName, "f9")==0)				return "K_F9";
	if(strcmp(keyName, "f10")==0)				return "K_F10";
	if(strcmp(keyName, "f11")==0)				return "K_F11";
	if(strcmp(keyName, "f12")==0)				return "K_F12";
	if(strcmp(keyName, "f13")==0)				return "K_F13";
	if(strcmp(keyName, "f14")==0)				return "K_F14";
	if(strcmp(keyName, "f15")==0)				return "K_F15";
	if(strcmp(keyName, "numlock")==0)			return "K_NUMLOCK";
	if(strcmp(keyName, "capslock")==0)			return "K_CAPSLOCK";
	if(strcmp(keyName, "scrollock")==0)			return "K_SCROLLOCK";
	if(strcmp(keyName, "right shift")==0)		return "K_RSHIFT";
	if(strcmp(keyName, "left shift")==0)		return "K_LSHIFT";
	if(strcmp(keyName, "right ctrl")==0)		return "K_RCTRL";
	if(strcmp(keyName, "left ctrl")==0)			return "K_LCTRL";
	if(strcmp(keyName, "right alt")==0)			return "K_RALT";
	if(strcmp(keyName, "left alt")==0)			return "K_LALT";
	if(strcmp(keyName, "right meta")==0)		return "K_RMETA";
	if(strcmp(keyName, "left meta")==0)			return "K_LMETA";
	if(strcmp(keyName, "left windows key")==0)	return "K_LSUPER";
	if(strcmp(keyName, "right windows key")==0)	return "K_RSUPER";
	if(strcmp(keyName, "mode shift")==0)		return "K_MODE";
	if(strcmp(keyName, "help")==0)				return "K_HELP";
	if(strcmp(keyName, "print screen")==0)		return "K_PRINT";
	if(strcmp(keyName, "sysrq")==0)				return "K_SYSREQ";
	if(strcmp(keyName, "break")==0)				return "K_BREAK";
	if(strcmp(keyName, "menu")==0)				return "K_MENU";
	if(strcmp(keyName, "power")==0)				return "K_POWER";
	if(strcmp(keyName, "euro")==0)				return "K_EURO";

	ERROR("unknown keyName '" << keyName << "'");
	return NULL;
}


char* tKey2Char(tKey key)
// Get a string definition of a tKey
{
	switch(key)
	{
		case key_action1:	return("key_action1");
		case key_action2:	return("key_action2");

		case key_1:			return("key_1");
		case key_2:			return("key_2");
		case key_3:			return("key_3");
		case key_4:			return("key_4");
		case key_5:			return("key_5");

		case key_left:		return("key_left");
		case key_right:		return("key_right");
		case key_up:		return("key_up");
		case key_down:		return("key_down");

		case key_cancel:	return("key_cancel");

//		case key_ESCAPE:	return("key_action1");
//		case key_ESCAPE:	return("key_action1");
	}

	ERROR("unknown key " << key);
	return NULL;
}
