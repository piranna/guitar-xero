//	GPL Jesus Leganes Combarro (Piranna)
//	piranna@gmail.com
//
// Commercial use license is available under apply to the author


#ifndef __Note_hpp__
#define __Note_hpp__


	// Note
class Note
{
private:
	bool active_;
	float start_;
	float finish_;

	Note* sig_;

protected:
	bool star_;

public:
	bool IsActive();
	bool IsLong();
	bool IsStar();

	void SetInactive();

	float GetStart();
	float GetFinish();

	void SetSig(Note* sig);
	Note* GetSig();

	Note(float start, float finish);
};


	// NoteStar
class NoteStar: public Note
{
public:
	NoteStar(float start, float finish);
};

#endif
