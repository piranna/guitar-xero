// Based on code from Kibitech, S.L.
//  *** Kournikova rulez!!! X-D ***

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
    #include <iostream>

	extern int loglevel;
	extern const char* logcoder;

	#define TRACE(type, txt)\
	{\
		std::cout << "[" << type << "] " << __PRETTY_FUNCTION__ << txt << std::endl;\
	}

	#define TRACEVAR(varName)\
	{\
		std::cout << __PRETTY_FUNCTION__ << ": " <<(std::string)#varName << " = " << varName << std::endl;\
	}

	#define TRACEVAR_HEX(coder, level, varName)\
	{\
		if(!coder || (!strcmp(coder, logcoder))\
			&& (level<=loglevel))\
		{\
			std::cout << level << ": " << (std::string)#varName << " = "\
						<< std::hex << varName << std::dec << std::endl;\
		}\
	}

	#define START()\
	{\
		std::cout << std::endl << "/== " << __PRETTY_FUNCTION__ << " started  ==\\" << std::endl;\
	}

	#define FINISH()\
	{\
		std::cout << "\\== " << __PRETTY_FUNCTION__ << " finished ==/" << std::endl << std::endl;\
	}

#else /*DEBUG*/
	#define TRACE(coder, level, type, txt)
	#define TRACEVAR(coder, level, txt)
	#define TRACEVAR_HEX(coder, level, txt)
	#define START()
	#define FINISH()
#endif /*DEBUG*/

#endif /*DEBUG_H*/
