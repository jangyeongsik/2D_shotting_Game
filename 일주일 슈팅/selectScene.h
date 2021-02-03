#pragma once
#include "gameNode.h"
class mainGame;

enum SELECTSTATE
{
	DIFFICULLTYSELECT,
	CHARATERSELECT
};

class selectScene : public gameNode
{ 
private:
	bool _isActivate;
	SELECTSTATE _state;
	image* _selection;
	mainGame* _mg;

	bool _isDifficulltySelect;
	bool _isMove;
	int _frameX;
	int _frameY;

public:
	selectScene() {}
	~selectScene() {}

	HRESULT init(mainGame* mg);
	void release();
	void update();
	void render();

	bool getIsActivate() { return _isActivate; }
};

