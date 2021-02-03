#pragma once
#include "bullet.h"

class bullet_player : public bullet
{
private:
	bool _isHoming;
	int _frameY;
	int _homingCount;
public:
	bullet_player() {}
	~bullet_player() {}
	virtual HRESULT init();
	virtual HRESULT init(float x, float y, float angle);
	virtual void release() ;
	virtual void update() ;
	virtual void render() ;
	void setIsHoming(bool isHoming, int charNum);
	void setAngle(float angle);
};
