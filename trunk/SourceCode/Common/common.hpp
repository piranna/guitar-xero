//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef common_h
#define common_h

enum tKey
{
	key_action1, key_action2,
	key_vibratto, key_tilt,
	key_1, key_2, key_3, key_4, key_5,
	key_left, key_right, key_up, key_down,
	key_cancel,
enumKeys
};


struct tColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};


void Append(char* cadena, char caracter);
void Unhead(char* cadena, int cut);
void Untail(char* cadena, int cut);
void Unspace(char* cadena);

char* GetText(char* original);

void GetFileExtension(char* path, char* dirPath, char* fileName);
void GetRandomFile(char* path, char* dirPath, char* fileName);

tColor* LoadButtonsColors();
tColor Char2tColor(char* car);
char* GetDefaultButtonColor(int num);

char* LoadTheme(char* option, char* def);

char* KeyName2PyGameKey(char* keyName);

// Input
char* tKey2Char(tKey key);
#endif
