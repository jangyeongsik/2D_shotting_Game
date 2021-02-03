#pragma once
#include "enemy.h"
class enemy_blue : public enemy
{
private:
	bool _isMove;
	bool _isLeft;

	float _dis;
public:
	enemy_blue() {}
	~enemy_blue() {}

	HRESULT init(float x, float y);
	HRESULT init( bool isLeft);
	void release();
	void update();
	void render();

	int getFireCount() { return _fireCount; }
	RECT getEnemyRect() { return _enemyRC; }
};

