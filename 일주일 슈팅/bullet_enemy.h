#pragma once
#include "bullet.h"
class bullet_enemy : public bullet
{
private:

	int _frameX;

public:
	bullet_enemy() {}
	~bullet_enemy() {}
	HRESULT init();
	HRESULT init(float x, float y,float angle);
	void release();
	void update();
	void render();
};

