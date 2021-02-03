#pragma once
#include "enemy.h"
class enemy_red : public enemy
{
private:
	bool _isLeft;
	bool _isMove;

public:
	enemy_red() {}
	~enemy_red() {}

	HRESULT init(float x, float y);
	HRESULT init(bool isLeft,float x, float y);
	void release();
	void update();
	void render();

	int getFireCount() { return _fireCount; }
	RECT getEnemyRect() { return _enemyRC; }
};

