#include "stdafx.h"
#include "itemManager.h"

itemManager* itemManager::_inst = 0;

HRESULT itemManager::init(int size)
{

	for (int i = 0; i < size; i++)
	{
		item* _item = new item;
		_item->init();
		_qItem.push(_item);
	}

	return S_OK;
}

void itemManager::makeItem(float x, float y, ITEMKIND kind)
{
	if (_qItem.size() == 0)
	{
		item* _item = new item;
		_item->init();
		_qItem.push(_item);
	}
	_qItem.front()->init(x, y, kind);
	_vItem.push_back(_qItem.front());
	_qItem.pop();
}

void itemManager::popItem(int arr)
{
	_vItem[arr]->init();
	_qItem.push(_vItem[arr]);
	_vItem.erase(_vItem.begin() + arr);
}
