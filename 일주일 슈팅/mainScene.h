#pragma once
#include "gameNode.h"
class mainGame;
class mainScene : public gameNode
{
private:
	bool _isActivate;
	int _frameX;

	mainGame* _mg;
public:
	mainScene() {}
	~mainScene() {}

	HRESULT init(mainGame* mg);
	void release();
	void update();
	void render();

	bool getIsActivate() { return _isActivate; }
};

