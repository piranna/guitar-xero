#include "GX_Common.hpp"

#include "error.h"
#include "ParserOptions.hpp"
#include "constants.hpp"


int GetOptionMultiple(char* options[], char* block, char* option)
// Get the value of a multiple option
{
	// Get num of available options in 'options[]'
	int numOption = 0;
	while(options[numOption])
		numOption++;
	if(!numOption)
	{
		ERROR("no options for block");
		return -1;
	};

	// Set numOption to the last 'options[]' position
	numOption--;

	// Compare all options in 'options[]' with the config file one
	// to get its position in 'options[]'
	ParserOptions parser(GUITARXERO_INI);
	parser.Read();

	while(numOption &&
			strcmp(parser.GetConfig(block, option),
					options[numOption])!=0)
		numOption--;

	// Return selected option
	return numOption;
}