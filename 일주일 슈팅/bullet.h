#pragma once
#include "gameNode.h"

class bullet : public gameNode
{
protected:
	bool _isActivate;

	float _x, _y;
	float _angle;
	RECT _bulletRC;

	image* _ig;

public:
	bullet() {}
	virtual~bullet() {}

	virtual HRESULT init(float x, float y, float angle) =0;
	virtual void release() =0;
	virtual void update() =0;
	virtual void render() =0;

	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRect() { return _bulletRC; }
	bool getIsActivate() { return _isActivate; }
	
};
