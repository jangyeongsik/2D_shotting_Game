#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "boss.h"


class mainGame;

enum PLAYSTAGE
{
	NOMAL,
	BOSS
};

class playScene :public gameNode
{
private:
	PLAYSTAGE _pstage;
	bool _isActivate;
	mainGame* _mg;
	player _player;
	enemyManager* _em;
	boss _boss;

public:
	playScene() {}
	~playScene() {}

	HRESULT init(mainGame* mg);
	void release();
	void update();
	void render();

	bool getIsActivate() { return _isActivate; }
};

