#include "stdafx.h"
#include "enemy_red.h"


HRESULT enemy_red::init(float x, float y)
{
	return S_OK;
}

HRESULT enemy_red::init(bool isLeft,float x, float y)
{
	_isActivate = true;
	_isMove = false;
	_kind = RED;

	_y = y;
	_ig = IMAGEMANAGER->findImage("enemy");
	_frameX = 0;
	_frameY = 0;
	_isLeft = isLeft;

	_enemyState = IDLE;

	if (_isLeft)
	{
		_angle = 0.f;
		_x = 0 - x;
	}
	else
	{
		_angle = PI;
		_x = 505 + x;

	}

	_fireCount = 0;
	_enemyRC = RectMake(_x, _y, 20, 20);
	return S_OK;
}

void enemy_red::release()
{
}

void enemy_red::update()
{

	switch (_enemyState)
	{
	case IDLE:
		_fireCount++;

		if (_fireCount % 60 == 0)
		{
			_fireCount = 0;
		}

		if (_isLeft)
		{
			if (_enemyRC.left > 24) _isMove = true;
			if (_enemyRC.right > 505) _isActivate = false;
			_x += cosf(0) * 5.f;
		}
		else
		{
			if (_enemyRC.right < 505) _isMove = true;
			if (_enemyRC.left < 24) _isActivate = false;
			_x += cosf(PI) * 5.f;
		}

		if (_isMove)
		{
			if (_isLeft)
			{

				_y -= sinf(_angle) * 3.f;
				_angle += 0.1f;
			}
			else
			{

				_y -= sinf(_angle) * 3.f;
				_angle += 0.1f;
			}
		}
		break;
	case DEAD:
		_ig = IMAGEMANAGER->findImage("enemyDeath");

		_frameTime += TIMEMANAGER->getElapsedTime();
		if (_frameTime > 0.05f)
		{
			_frameTime -= 0.05f;
			_frameX++;
			if (_frameX > _ig->getMaxFrameX())
			{
				_isActivate = false;
			}
		}
		break;
	}
	
	


	_enemyRC = RectMake(_x, _y, 20, 20);
}

void enemy_red::render()
{
	switch (_enemyState)
	{
	case IDLE:
		if (_isActivate) _ig->frameRender(getMemDC(), _x, _y, 0, 0);
		break;
	case DEAD:
		_ig->frameRender(getMemDC(), _x, _y, _frameX, _frameY);
		break;
	}
}
