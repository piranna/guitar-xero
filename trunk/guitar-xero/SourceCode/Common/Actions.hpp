#ifndef Actions_hpp
#define Actions_hpp


enum tAction {FRET_1, FRET_2, FRET_3, FRET_4, FRET_5, PICK, TILT, VIBRATTO,
			UP, DOWN, MORE, LESS, SELECT, BACK,
			enumActions};


class Actions
{
private:
	bool action_[enumActions];

public:
	static Actions* actions_;

	void ResetActions();

	void SetAction(tAction action, bool state);
	bool GetAction(tAction action);

	Actions();
};

#endif
