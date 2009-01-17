#ifndef List_hpp
#define List_hpp


class ListData{};

class ListEntry
{
private:
	ListData* data_;
	ListEntry* sig_;

public:
	void SetSig(ListEntry* sig);
	ListEntry* GetSig();

	void SetData(ListData* data);
	ListData* GetData();

	ListEntry(ListData* data);
	~ListEntry();
};

class List
{
private:
	ListEntry* head_;

public:
	void Reset();
	void Append(ListData* data);
	void RemoveLast();
	void Set(int pos, ListData* data);

	ListEntry* GetList();
	ListData* GetData(int option);
	unsigned int Length();

	List();
	~List();
};

#endif
