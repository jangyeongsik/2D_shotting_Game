#include "stdafx.h"
#include "bullet_player.h"


HRESULT bullet_player::init()
{
	_x = 0;
	_y = 0;
	_angle = 0;
	_bulletRC = RectMake(0, 0, 0, 0);
	_isHoming = false;
	_frameY = 0;
	_homingCount = 0;
	_isActivate = false;
	return S_OK;
}

HRESULT bullet_player::init(float x, float y, float angle)
{
	_x = x;
	_y = y;
	_angle = angle;
	_bulletRC = RectMake(_x, _y, 10, 10);
	_isHoming = false;
	_homingCount = 0;
	_isActivate = true;

	return S_OK;
}

void bullet_player::release()
{
}

void bullet_player::update()
{

	if (_isHoming) _homingCount++;
	_x += cosf(_angle) * 6.f;
	_y -= sinf(_angle) * 6.f;
	
	if (_isHoming) _bulletRC = RectMake(_x, _y, 10, 10);
	else _bulletRC = RectMakeCenter(_x + _ig->getFrameWidth()/2, _y + 8 , 12, 15);

	if (_bulletRC.left < 24 || _bulletRC.right >505 || _bulletRC.top < 12) _isActivate = false;

}

void bullet_player::render()
{
	if (_isActivate)
	{
		//Rectangle(getMemDC(), _bulletRC);
		if (_isHoming) _ig->render(getMemDC(), _x, _y);
		else _ig->frameRender(getMemDC(), _x, _y, _frameY, 0);
	}
}

void bullet_player::setIsHoming(bool isHoming, int charNum)
{
	_isHoming = isHoming;
	_frameY = charNum;
	if (_isHoming)
	{
		_ig = IMAGEMANAGER->findImage("plHomingBullet");
	}
	else
	{
		_ig = IMAGEMANAGER->findImage("plBullet");
	}
}

void bullet_player::setAngle(float angle)
{
	
	if (_isHoming && _homingCount >= 20)
	{
		_angle = angle;
		_homingCount = 20;
	}
}
