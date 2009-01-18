//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef error_h
#define error_h

#include <iostream>

#define WARNING(message)\
{\
	std::cerr << "[WARNING] " << __PRETTY_FUNCTION__\
			<< ": " << message << std::endl;\
}

#define ERROR(message)\
{\
	std::cerr << "[ERROR] " << __PRETTY_FUNCTION__\
			<< ": " << message << std::endl;\
}

#define FATAL(message)\
{\
	std::cerr << "[FATAL] " << __PRETTY_FUNCTION__\
			<< ": " << message << std::endl;\
	exit(1);\
}

#endif
