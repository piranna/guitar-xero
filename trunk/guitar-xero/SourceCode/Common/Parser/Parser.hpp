#ifndef Parser_hpp
#define Parser_hpp

class Parser
{
protected:
	char* file_;

	virtual void Reset()=0;

public:
	bool Read();
	virtual bool Merge()=0;
	virtual void Write()=0;

	void SetFile(char* file);

	Parser(char* file);
};

#endif
