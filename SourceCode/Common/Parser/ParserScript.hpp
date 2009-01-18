//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef ParserOptionsScript_hpp
#define ParserOptionsScript_hpp

/*
	ParserScript

	This parser get the path of a song script (subtitles and images)
	and process it. The script is stored in memory and NOT deleted
	when the class is deleted since it should remain so it can be used,
	so it must be deleted after it has been used by hand.
*/

#include "Parser.hpp"

#include <string.h>

//typedef enum{START, FINISH, TYPE, TextModeScript} tModeScript;
typedef enum{TEXTTYPE, PIC} tTypeEntry;


// ScriptEntry
class ScriptEntry
{
public:
	long start_;
	long finish_;
	tTypeEntry type_;
	char text_[256];
	ScriptEntry* sig_;

	ScriptEntry(unsigned int start, unsigned int finish, tTypeEntry type,
			char* text);
};


// ParserScript
class ParserScript: public Parser
{
private:
//	tModeScript mode_;
	ScriptEntry* script_;

	void Reset();

	void Add(long start, long finish, tTypeEntry type, char* text);

public:
	bool Merge();
	void Write();

	ScriptEntry* GetSubtitles();

	ParserScript(char* file);
	~ParserScript();
};

#endif
