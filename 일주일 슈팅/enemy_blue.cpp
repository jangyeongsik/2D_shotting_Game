#include "stdafx.h"
#include "enemy_blue.h"

HRESULT enemy_blue::init(float x, float y)
{
	return S_OK;
}

HRESULT enemy_blue::init( bool isLeft)
{
	_ig = IMAGEMANAGER->findImage("enemy");
	_isActivate = true;
	_isLeft = isLeft;
	_isMove = false;
	_kind = BLUE;
	_enemyState = IDLE;


	if (_isLeft)
	{
		_x = 24;
		_y = 0;
		_angle = PI;
	}
	else
	{
		_x = 505;
		_y = 0;
		_angle = 0;
	}

	_fireCount = 0;
	_dis = (505 - 24) / 3;

	return S_OK;
}

void enemy_blue::release()
{
}

void enemy_blue::update()
{

	
	switch (_enemyState)
	{
	case IDLE:
		_fireCount++;

		if (_fireCount % 80 == 0)
		{
			_fireCount = 0;
		}

		if (_isLeft)
		{
			_x = cosf(_angle) * 250 + 248;
			_y = sinf(_angle) * 240;
			_angle -= 0.02f;

			if (_x > 250)
			{
				_isMove = true;
			}

			if (_isMove && _y < 0)
			{
				_isActivate = false;
			}
		}
		else
		{
			_x = cosf(_angle) * 250 + 248;
			_y = sinf(_angle) * 240;
			_angle += 0.02f;

			if (_x > 250)
			{
				_isMove = true;
			}

			if (_isMove && _y < 0)
			{
				_isActivate = false;
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

void enemy_blue::render()
{
	switch (_enemyState)
	{
	case IDLE:
		_ig->frameRender(getMemDC(), _x, _y, 1, 0);
		break;
	case DEAD:
		_ig->frameRender(getMemDC(), _x, _y, _frameX, _frameY);
		break;
	}
}
