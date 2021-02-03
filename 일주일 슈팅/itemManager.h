#pragma once
#include "item.h"

class itemManager
{
private:
	queue<item*> _qItem;
	vector<item*> _vItem;

	static itemManager* _inst;

	itemManager() {}
	~itemManager() {}
public:
	
	HRESULT init(int size);
	void makeItem(float x, float y, ITEMKIND kind);
	void popItem(int arr);


	vector<item*> getVItem() { return _vItem; }

	
	static itemManager* getInstance()
	{
		if (!_inst) _inst = new itemManager;
		return _inst;
	}
	void release()
	{
		delete _inst;
		_inst = nullptr;
	}
};

