#include "stdafx.h"
#include "bullet_enemy.h"

HRESULT bullet_enemy::init()
{

	_x = 0;
	_y = 0;
	_angle = 0;
	_isActivate = false;
	_ig = IMAGEMANAGER->findImage("bullet");
	_frameX = 0;


	return E_NOTIMPL;
}

HRESULT bullet_enemy::init(float x, float y, float angle)
{
	_x = x;
	_y = y;
	_angle = angle;
	_isActivate = true;
	_frameX = GetRandom(16);
	_bulletRC = RectMake(_x, _y, 16, 16);

	return E_NOTIMPL;
}

void bullet_enemy::release()
{
}

void bullet_enemy::update()
{
	_x += cosf(_angle) * 5.f;
	_y -= sinf(_angle) * 5.f;

	if(_bulletRC.left < 24 || _bulletRC.right > 505 || _bulletRC.top < 12 || _bulletRC.bottom > 575) _isActivate = false;

	_bulletRC = RectMake(_x, _y, 16, 16);
}

void bullet_enemy::render()
{
	_ig->frameRender(getMemDC(), _x, _y, _frameX, 0);
}
