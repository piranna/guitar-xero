#ifndef __Input_hpp__
#define __Input_hpp__

#include "Actions.hpp"
#include "common.hpp"


enum tInputMode
{
	EVENT, TEXTMODE, KEYNAME
};

class Input
{
protected:
	Actions* actions_;
	char character_;
	char* keyName_;
	tInputMode mode_;

	void GetActionKeyDown(tKey key);
	void GetActionKeyUp(tKey key);

	Input(Actions* actions);

public:
	static Input* input_;
	static char* libraries_[];
	static void Select(Actions* actions);

	virtual void GetActions()=0;
	virtual void LoadKeys()=0;

	virtual tInputMode GetMode()=0;
	virtual void SetMode(tInputMode)=0;
	virtual char GetCharacter()=0;
	virtual char* GetKeyName()=0;
};

#endif
