//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef Video_SDL
#define Video_SDL

#include "VideoSDL_Base.hpp"


class VideoSDL: public VideoSDL_Base
{
private:
	bool InitScreen();
	bool CanRender3D();

	void Flip();

	void FilledCircle(int x, int y, int radius,
						unsigned char r,
						unsigned char g,
						unsigned char b,
						unsigned char a);
public:
	static void Init();

	VideoSDL();
};

#endif
