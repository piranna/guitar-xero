#include "ParserScript.hpp"

#include "common.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"


// ScriptEntry
ScriptEntry::ScriptEntry(unsigned int start, unsigned int finish,
						tTypeEntry type, char* text):
	start_(start),
	finish_(finish),
	type_(type),
	sig_(NULL)
{
	strlcpy(text_, text, 256);
}


// ParserScript
void ParserScript::Reset()
// Clear the script
{
	while(script_)
	{
		ScriptEntry* auxSubtitle = script_;
		script_ = script_->sig_;
		delete(auxSubtitle);
	};
}

void ParserScript::Add(long start, long finish, tTypeEntry type,
						char* text)
// Add a script entry to the script list
{
	if(script_)
	{
		ScriptEntry* auxSubtitle = script_;
		while(auxSubtitle->sig_)
		{
			if(auxSubtitle->start_ > start)	// Start of new is earlier
			{
				ScriptEntry* aux = auxSubtitle;
				auxSubtitle = new ScriptEntry(start, finish, type, text);
				auxSubtitle->sig_ = aux;
				return;
			};

			auxSubtitle = auxSubtitle->sig_;
		};
		auxSubtitle->sig_ = new ScriptEntry(start, finish, type, text);
	}
	else
		script_= new ScriptEntry(start, finish, type, text);
}

bool ParserScript::Merge()
// Merge the file with the current data (or any, if parser was reset)
// Return if was sucesful
{
	FILE* fe=fopen(file_, "r");
	if(!fe)
		return false;

	char text[300];
	while(fgets(text, 300, fe))
	{
		if(text[0]!='#')
		{
			long start = atol(strtok(text, " \t\n"));
			long finish = atol(strtok(NULL, " \t\n"));

			tTypeEntry type;
			if(strcmp(strtok(NULL, " \t\n"), "text"))
				type=PIC;
			else
				type=TEXTTYPE;

			strlcpy(text, strtok(NULL, "\n"), 300);
			Unspace(text);
			Add(start, finish, type, text);
		};
	};

	fclose(fe);

	return true;
}

void ParserScript::Write()
// Write the current script to the selected file
{
	FILE* fe=fopen(file_, "w");
	if(!fe)
	{
		ERROR("Unable to write file " << file_);
		return;
	};

	ScriptEntry* auxSubtitle = script_;
	while(auxSubtitle)
	{
		char type[5];
		if(auxSubtitle->type_=TEXTTYPE)
			strcpy(type, "text");
		else
			strcpy(type, "pic");
		// [TO-DO] put comment
		// [TO-DO] put correct number width
		fprintf(fe, "%i %i %s %s\n", auxSubtitle->start_,
					auxSubtitle->finish_, type, auxSubtitle->text_);
	};
	fclose(fe);
}

ScriptEntry* ParserScript::GetSubtitles()
// Return the script
{
	return script_;
}


ParserScript::ParserScript(char* file):
	Parser(file),
	script_(NULL)
{
//	mode_=START;
}

ParserScript::~ParserScript()
{};
