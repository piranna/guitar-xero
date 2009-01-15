#ifndef ParserOptions_hpp
#define ParserOptions_hpp

#include "Parser.hpp"

#include <string.h>


typedef enum
{
	BLOCK, OPTION, VALUE
} tModeOptions;


// clsToken
class clsToken
{
public:
	char option_[256];
	char value_[256];
	clsToken* sig_;

	clsToken(char* option, char* value);
};


// clsBlock
class clsBlock
{
public:
	char name_[256];
	clsToken* tokens_;
	clsBlock* sig_;

	clsBlock(char* name);
};


// ParserOptions
class ParserOptions: public Parser
{
private:
	tModeOptions mode_;
	clsBlock* options_;

	void Reset();

	void AddOption(char* block, char* option, char* value);

public:
	bool Merge();
	void Write();

	void SetConfig(char* block, char* option, char* value);
	char* GetConfig(char* block, char* option);
	char* GetConfig(char* block, char* option, char* def);


	ParserOptions(char* file);
	~ParserOptions();
};

#endif
