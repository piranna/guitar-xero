//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef GX_Graphic_hpp
#define GX_Graphic_hpp

#include "common.hpp"


class GX_Graphic
{
public:
	static GX_Graphic* Make(int w, int h);
	static GX_Graphic* Make(char* path, int w, int h);
	static GX_Graphic* Make(char* text, char* fontPath, char* fontName, char size,
							tColor color);

	virtual void Draw(int,int)=0;
	virtual int GetWidth()=0;
	virtual int GetHeight()=0;

	virtual void HLine(int x1, int x2, int y, unsigned char r,
						unsigned char g, unsigned char b)=0;
	virtual void VLine(int x, int y1, int y2, unsigned char r,
						unsigned char g, unsigned char b)=0;
	virtual void Box(int x1, int y1, int x2, int y2, unsigned char r,
						unsigned char g, unsigned char b)=0;
	virtual void Circle(int x, int y, int radius, unsigned char r,
						unsigned char g, unsigned char b)=0;

	virtual void Blit(GX_Graphic*, int,int)=0;
	virtual void Fill(int,int, int,int,
						unsigned char,unsigned char,unsigned char)=0;
	virtual void Zoom(int,int)=0;
	virtual GX_Graphic* GetZoom(int,int)=0;
};

#endif