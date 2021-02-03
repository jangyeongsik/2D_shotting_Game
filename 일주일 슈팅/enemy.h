#pragma once
#include "gameNode.h"

enum ENEMYKIND
{
	RED,
	BLUE
};

enum ENEMYSTATE
{
	IDLE,
	DEAD
};

class enemy : public gameNode
{
protected:
	ENEMYKIND _kind;
	ENEMYSTATE _enemyState;
	bool _isActivate;
	float _x, _y;
	float _angle;
	RECT _enemyRC;
	image* _ig;

	float _frameTime;
	int _frameX;
	int _frameY;

	int _fireCount;

public:
	enemy() {}
	virtual ~enemy() {}


	virtual HRESULT init(float x, float y) = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool getIsActivate() { return _isActivate;}
	float getX() { return _x; }
	float getY() { return _y; }
	int getFireCount() { return _fireCount; }
	RECT getEnemyRect() { return _enemyRC; }
	ENEMYKIND getEnemyKind() { return _kind; }
	void setEnemyState(ENEMYSTATE state) { _enemyState = state; }
	ENEMYSTATE getEnemyState() { return _enemyState; }
};

