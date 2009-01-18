//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef Video_hpp
#define Video_hpp

#include <stdlib.h>

#include "common.hpp"


class Video
{
public:
	static Video* video_;
	static char* libraries_[];
	static void Select();

	virtual bool InitScreen()=0;
	virtual char** GetVideoModes()=0;
	virtual bool CanRender3D()=0;

	virtual void Flip()=0;

	virtual int GetWidth()=0;
	virtual int GetHeight()=0;

	virtual void FilledCircle(int x, int y, int radius,
							unsigned char r,
							unsigned char g,
							unsigned char b,
							unsigned char a)=0;
};

#endif
