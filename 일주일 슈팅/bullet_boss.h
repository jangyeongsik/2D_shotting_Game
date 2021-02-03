#pragma once
#include "gameNode.h"

enum BOSSBULLETPATERN
{
	PATERN1, // 원형으로 퍼지기만 한다
	PATERN2, 
	PATERN3,
	PATERN4,
	PATERN5,
	PATERN6,
	PATERN7,
};

enum BOSSBULLETSIZE
{
	BOSSBULLET_BIG,
	BOSSBULLET_SMALL,
	BOSSBULLET_MINI
};

class bullet_boss : public gameNode
{
private:
	image* _bulletImage;
	BOSSBULLETPATERN _bulletPatern;
	BOSSBULLETSIZE _bulletSize;

	float _x, _y, _speed, _angle;
	float _startX, _startY;
	float _distance;
	RECT _bulletRC;

	bool _isActivate;
	bool _isMoveStart;
	bool _isReady;
	bool _isUp;

	int _color;
	int _moveCount;
	int _moveTime;

public:
	bullet_boss() {}
	~bullet_boss() {}

	HRESULT init();
	HRESULT init(float x, float y, float angle,float speed, BOSSBULLETSIZE size, BOSSBULLETPATERN patern, int color , bool isUp = false,float  dist = 0);
	void update(float angle);
	void release();
	void render();
	float getX() { return _x; }
	float getY() { return _y; }
	float getAngle() { return _angle; }
	RECT getRect() { return _bulletRC; }

	void setIsMove(bool move) { _isMoveStart = move; }
	bool getIsReady() { return _isReady; }
	bool getIsActivate() { return _isActivate; }
};

