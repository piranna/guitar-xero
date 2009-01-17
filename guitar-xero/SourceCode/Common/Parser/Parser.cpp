#include "Parser.hpp"


bool Parser::Read()
// Read the selected file
{
	Reset();

	return Merge();
}

void Parser::SetFile(char* file)
// Set the selected file
{
	file_ = file;
}


Parser::Parser(char* file):
	file_(file)
{}