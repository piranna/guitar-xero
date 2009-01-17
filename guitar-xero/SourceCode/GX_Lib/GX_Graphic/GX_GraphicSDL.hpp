#include "GX_Graphic.hpp"

#include "SDL/SDL.h"

#include "common.hpp"


class GX_GraphicSDL: public GX_Graphic
{
private:
	SDL_Surface* surface_;

	void Draw(int x, int y);
	int GetWidth();
	int GetHeight();

	void HLine(int x1, int x2, int y, unsigned char r, unsigned char g,
				unsigned char b);
	void VLine(int x, int y1, int y2, unsigned char r, unsigned char g,
				unsigned char b);
	void Box(int x1, int y1, int x2, int y2, unsigned char r,
			unsigned char g, unsigned char b);
	void Circle(int x, int y, int radius, unsigned char r,
				unsigned char g, unsigned char b);

	void Blit(GX_Graphic* other, int x, int y);
	void Fill(int x,int y, int w,int h,
				unsigned char r,unsigned char g,unsigned char b);
	void Zoom(int w, int h);
	GX_GraphicSDL* GetZoom(int w, int h);

	GX_GraphicSDL();

public:
	GX_GraphicSDL(int w, int h);
	GX_GraphicSDL(char* path, int w, int h);
	GX_GraphicSDL(char* text, char* fontPath, char size, tColor color);
	~GX_GraphicSDL();
};
