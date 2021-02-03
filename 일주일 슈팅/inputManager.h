#pragma once
#include "singletonBase.h"
#define KEYMAX 256
class inputManager : public singletonBase<inputManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	inputManager() {}
	~inputManager() {}

	HRESULT init();

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

};

