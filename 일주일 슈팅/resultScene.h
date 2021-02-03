#pragma once
#include "gameNode.h"

class mainGame;

enum RESULTSCENE
{
	ISGAMECLEAR,
	ISGAMEOVER
};

class resultScene : public gameNode
{
private:

	mainGame* _mg;

	int _alpha;

public:
	resultScene() {}
	~resultScene() {}

	HRESULT init(mainGame* mg);
	void release();
	void update();
	void render();
};

