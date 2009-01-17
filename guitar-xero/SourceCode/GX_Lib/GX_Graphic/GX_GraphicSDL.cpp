#include "GX_GraphicSDL.hpp"

#ifdef __APPLE__
	#include "SDL_image/SDL_image.h"
	#include "SDL_rotozoom.h"
	#include "SDL_ttf/SDL_ttf.h"
	#include "SDL_gfxPrimitives.h"
#else
	#include "SDL/SDL_image.h"
	#include "SDL/SDL_rotozoom.h"
	#include "SDL/SDL_ttf.h"
	#include "SDL/SDL_gfxPrimitives.h"
#endif

#include "error.h"

#include "VideoSDL.hpp"


void GX_GraphicSDL::Draw(int x, int y)
// Draw graphic at (x,y) coordinates of the screen
{
	if(surface_)
	{
		SDL_Rect dest = {x,y, surface_->w,surface_->h};

		SDL_BlitSurface(surface_, NULL,
						((VideoSDL*)Video::video_)->GetScreen(), &dest);
	}
}

int GX_GraphicSDL::GetWidth()
// Return width of the graphic
{
	if(surface_)
		return surface_->w;

	return NULL;
}

int GX_GraphicSDL::GetHeight()
// Return height of the surface
{
	if(surface_)
		return surface_->h;

	return NULL;
}


void GX_GraphicSDL::HLine(int x1, int x2, int y, unsigned char r,
							unsigned char g, unsigned char b)
// Draw a horizontal line on the graphic
{
	hlineRGBA(surface_, x1,x2, y, r,g,b,255);
}

void GX_GraphicSDL::VLine(int x, int y1, int y2, unsigned char r,
							unsigned char g, unsigned char b)
// Draw a vertical line on the graphic
{
	vlineRGBA(surface_, x, y1,y2, r,g,b,255);
}

void GX_GraphicSDL::Box(int x1, int y1, int x2, int y2, unsigned char r,
						unsigned char g, unsigned char b)
// Draw a rectagle on the graphic
{
	boxRGBA(((VideoSDL*)Video::video_)->GetScreen(),
			x1,y1, x2,y2, r,g,b,255);
}

void GX_GraphicSDL::Circle(int x, int y, int radius, unsigned char r,
							unsigned char g, unsigned char b)
// Draw a circle on the graphic
{
	circleRGBA(((VideoSDL*)Video::video_)->GetScreen(),
				x,y, radius, r,g,b,255);
}


void GX_GraphicSDL::Blit(GX_Graphic* other, int x, int y)
// Blit the image 'other' on the graphic at coordinates (x,y)
{
	SDL_Rect dest = {x,y, 0,0};

	SDL_BlitSurface(((GX_GraphicSDL*)other)->surface_, NULL,
					surface_, &dest);
}

void GX_GraphicSDL::Fill(int x,int y, int w,int h,
						unsigned char r,unsigned char g,unsigned char b)
// Fill the graphic with a color at coordinates (x,y, w,h)
{
	SDL_Rect dest = {x,y, w,h};
	SDL_FillRect(surface_, &dest, SDL_MapRGB(surface_->format, r,g,b));
}

void GX_GraphicSDL::Zoom(int w, int h)
// Zoom the image to adjust to w and h sizes.
// If filled with NULL then doesn't zoom that coordinate
{
	GX_GraphicSDL* auxSurface = GetZoom(w, h);

	if(auxSurface!=this)
		if(auxSurface->surface_)	// If resize was sucesful,
		{							//	replace surface
			SDL_FreeSurface(surface_);
			surface_ = auxSurface->surface_;
		}
		else
			ERROR("usable to resize surface");
}

GX_GraphicSDL* GX_GraphicSDL::GetZoom(int w, int h)
// Zoom the image to adjust to w and h sizes and return it
// If filled with NULL then doesn't zoom that coordinate
{
	GX_GraphicSDL* auxGraphic = this;

	if(w || h)	// If is set width or height resize surface
	{
		float propW, propH;		// Calc proportions of the surface

		if(w && h)
		{
			propW = w/float(surface_->w);
			propH = h/float(surface_->h);
		}
		else if(w)
		{
			propW = w/float(surface_->w);
			propH = propW;
		}
		else
		{
			propH = h/float(surface_->h);
			propW = propH;
		}

		// Resize surface
		SDL_Surface* auxSurface = zoomSurface(surface_, propW, propH, 1);
		if(auxSurface)
		{
			auxGraphic = new GX_GraphicSDL();
			auxGraphic->surface_ = auxSurface;
		}
	}
	return auxGraphic;
}


// Empty
GX_GraphicSDL::GX_GraphicSDL():
	surface_(NULL)
{}


//	Empty Image
GX_GraphicSDL::GX_GraphicSDL(int w, int h):
	surface_(SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0,0,0,0))
{
	if(!surface_)
		ERROR("unable to create surface " << w << "x" << h);
}


//	Image
GX_GraphicSDL::GX_GraphicSDL(char* path, int w, int h):
	surface_(IMG_Load(path))
{
	if(surface_)
		Zoom(w, h);

	else
		ERROR("unable to load image " << path);
}


//	Text
GX_GraphicSDL::GX_GraphicSDL(char* text, char* fontPath, char size,
							tColor color):
	surface_(NULL)
{
	TTF_Font* font = TTF_OpenFont(fontPath, size);

	if(font)
	{
		SDL_Color sdlColor= {color.r, color.g, color.b};

		surface_ = TTF_RenderText_Blended(font, GetText(text), sdlColor);

		if(!surface_)
			ERROR("unable to render " << text);

		TTF_CloseFont(font);
	}
	else
		ERROR("unable to load font " << fontPath);
}

GX_GraphicSDL::~GX_GraphicSDL()
{
	SDL_FreeSurface(surface_);
}