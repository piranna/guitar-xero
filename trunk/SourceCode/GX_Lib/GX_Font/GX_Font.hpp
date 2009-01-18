//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


class GX_Font
{
protected:
	static void* font_;

	static char* fontPath_;
	static char* fontName_;
	static int fontSize_;

public:
	static void* Load(char* fontPath, char* fontName, int fontSize);
};
