//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#include "MenuAlbum.hpp"

#include "constants.hpp"


MenuAlbum::MenuAlbum(char* path):
	MenuDirElement(path, false)
{
	char auxPath[256];
	GetFileExtension(auxPath, path, "cover");

	image_ = GX_Graphic::Make(auxPath, 200, 200);

	if(!image_)	// If there's no cover image,
	{			// get CD cover image and impress a handwritten label
		GetFileExtension(auxPath, MEDIA_DIR, "compactDisk");
		image_ = GX_Graphic::Make(auxPath, 200, 200);

		// Get dir name
		char* auxText = path;
		char* auxIndex = path;
		while(*auxText)
		{
			if(*auxText=='/')
				auxIndex=auxText;
			auxText++;
		}

		// Render text
		tColor color = {0, 0, 0};

		GX_Graphic* textImage = GX_Graphic::Make(auxIndex, MEDIA_DIR, "JustMeAgainDownHere.ttf", 25,
												color);
		image_->Blit(textImage,
					(image_->GetWidth()-textImage->GetWidth())/2.0,
					(image_->GetHeight()-textImage->GetHeight())/2.0);
		delete(textImage);
	}
}