#include "MenuSong.hpp"

#include "common.hpp"
#include "constants.hpp"

#include "ParserOptions.hpp"


MenuSong::MenuSong(char* path):
	MenuDirElement(path, true)
{
	char auxPath[256];
	GetFileExtension(auxPath, path, "label");
	GX_Graphic* tmpImage = GX_Graphic::Make(auxPath, 0, 0);

	if(tmpImage)	// There is label
	{
		if(tmpImage->GetWidth() == tmpImage->GetHeight())	// CD
		{
			tmpImage->Zoom(200, 200);
			image_ = tmpImage;
		}

		else												// Cassette
		{
			GetFileExtension(auxPath, MEDIA_DIR, "cassette");
			image_ = GX_Graphic::Make(auxPath, 0, 0);

			image_->Blit(tmpImage, 20, 5);

			delete(tmpImage);
		}
	}
	else			// Handwritten text
	{
		GetFileExtension(auxPath, MEDIA_DIR, "cassette");
		image_ = GX_Graphic::Make(auxPath, 0, 0);

		sprintf(auxPath, "%s/song.ini", path);
		ParserOptions parser(auxPath);
		parser.Read();

		char text[256];
		tColor color = {0, 0, 0};

		strcpy(text, parser.GetConfig("song", "name"));

		char fontPath[256];
		sprintf(fontPath, "%s/%s", MEDIA_DIR, "JustMeAgainDownHere.ttf");

		GX_Graphic* auxText = GX_Graphic::Make(text, fontPath, 25, color);
		image_->Blit(auxText, 50, 5);
		delete(auxText);

		strcpy(text, parser.GetConfig("song", "artist"));
		auxText = GX_Graphic::Make(text, fontPath, 25, color);
		image_->Blit(auxText, 50, 30);
		delete(auxText);
	}
}