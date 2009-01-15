#include "ParserOptions.hpp"

#include "common.hpp"

#include <stdio.h>
#include <string.h>

#include "error.h"


// clsToken
clsToken::clsToken(char* option, char* value):
	sig_(NULL)
{
	strlcpy(option_, option, 256);
	strlcpy(value_, value, 256);
}


// clsBlock
clsBlock::clsBlock(char* name):
	tokens_(NULL),
	sig_(NULL)
{
	strlcpy(name_, name, 256);
}


// ParserOptions
void ParserOptions::Reset()
// Clear the parser options list
{
	while(options_)
	{
		while(options_->tokens_)
		{
			clsToken* auxToken = options_->tokens_;
			options_->tokens_ = options_->tokens_->sig_;
			delete(auxToken);
		};
		clsBlock* auxBlock = options_;
		options_ = options_->sig_;
		delete(auxBlock);
	};
}

void ParserOptions::AddOption(char* block, char* option, char* value)
// Add an option to the parser list
{
	if(options_)
	{
		clsBlock* auxBlock=options_;
		while(auxBlock->sig_ && strcmp(auxBlock->name_, block))
			auxBlock=auxBlock->sig_;

		if(strcmp(auxBlock->name_, block)==0)
		{
			if(auxBlock->tokens_)
			{
				clsToken* auxToken=auxBlock->tokens_;
				while(auxToken->sig_ && strcmp(auxToken->option_, option))
					auxToken = auxToken->sig_;

				if(strcmp(auxToken->option_, option))
					auxToken->sig_ = new clsToken(option, value);
				else
					strcpy(auxToken->value_, value);
			}
			else
				auxBlock->tokens_ = new clsToken(option, value);
		}
		else
		{
			auxBlock->sig_ = new clsBlock(block);
			auxBlock->sig_->tokens_ = new clsToken(option, value);
		};
	}
	else
	{
		options_ = new clsBlock(block);
		options_->tokens_ = new clsToken(option, value);
	};
}

bool ParserOptions::Merge()
// Merge the current file with the parser list
// and return if was sucesfull
{
	FILE* fe=fopen(file_, "r");
	if(!fe)
		return false;

	int a;

	char block[256]="";
	char option[256]="";
	char value[1024]="";

	bool isComment=false;

	do
	{
		a=fgetc(fe);
		if((a=='\n') || (a==EOF))	// If 'end of line' or 'end of file'
		{
			if((mode_==VALUE) && !isComment)
			{
				Unspace(value);
				AddOption(block, option, value);
			}
			strcpy(option, "");
			strcpy(value, "");
			mode_=OPTION;
			isComment=false;
		}
		else if(!isComment)			// If is not a comment
			switch(a)
			{
				// Block start
				case '[':
					if(mode_==VALUE)
						Append(value, a);
					else
					{
						strcpy(block, "");
						mode_=BLOCK;
					};
				break;

				// Block finish
				case ']':
					if(mode_==VALUE)
						Append(value, a);
				break;

				// End of option and start of value
				case '=':
					if(mode_==OPTION)
					{
						Unspace(option);
						mode_=VALUE;
					}
					else if(mode_==VALUE)
						Append(value, a);
				break;

				// General chars
				default:
					switch(mode_)
					{
						case BLOCK:
							Append(block, a);
							break;
						case OPTION:
							if(a=='#' && !strcmp(option, ""))
								isComment=true;
							else
								Append(option, a);
							break;
						case VALUE:
							Append(value, a);
							break;
					};
				break;
			};
	}while(a!=EOF);

	fclose(fe);

	return true;
}

void ParserOptions::Write()
// Write parser list to current file
{
	FILE* fe=fopen(file_, "w");
	if(!fe)
	{
		ERROR("Unable to write file " << file_);
		return;
	};

	clsBlock* auxBlock = options_;
	while(auxBlock)
	{
		fprintf(fe, "[%s]\n", auxBlock->name_);
		clsToken* auxToken = auxBlock->tokens_;
		while(auxToken)
		{
			fprintf(fe, "%s = %s\n", auxToken->option_, auxToken->value_);
			auxToken=auxToken->sig_;
		};
		auxBlock=auxBlock->sig_;
	};
	fclose(fe);
}


void ParserOptions::SetConfig(char* block, char* option, char* value)
// Add option to parser list and write it to current file
{
	AddOption(block, option, value);
	Write();
}

char* ParserOptions::GetConfig(char* block, char* option)
// Get option from config file, default is option
{
	return GetConfig(block, option, option);
}

char* ParserOptions::GetConfig(char* block, char* option, char* def)
// Get option from config file
{
	clsBlock* auxBlock=options_;
	while(auxBlock)
	{
		if(strcmp(auxBlock->name_, block)==0)
		{
			clsToken* auxToken=auxBlock->tokens_;
			while(auxToken)
			{
				if(strcmp(auxToken->option_, option)==0)
					return(auxToken->value_);
				auxToken = auxToken->sig_;
			};
		};
		auxBlock = auxBlock->sig_;
	};

	return def;
}


ParserOptions::ParserOptions(char* file):
	Parser(file),
	mode_(BLOCK),
	options_(NULL)
{}

ParserOptions::~ParserOptions()
{
	Reset();
}
