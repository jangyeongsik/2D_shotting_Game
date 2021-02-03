#include "stdafx.h"
#include "bullet_boss.h"

HRESULT bullet_boss::init()
{
	_bulletImage = IMAGEMANAGER->findImage("bullet");
	_x = 0;
	_y = 0;
	_startX = 0;
	_startY = 0;
	_speed = 0;
	_angle = 0;
	_isActivate = false;
	_isMoveStart = false;
	_isReady = false;
	_bulletRC = RectMakeCenter(_x, _y, 15, 15);
	_moveTime = 0;

	return S_OK;
}

HRESULT bullet_boss::init(float x, float y, float angle, float speed, BOSSBULLETSIZE size, BOSSBULLETPATERN patern, int color, bool isUp, float dist)
{
	_x = x;
	_y = y;
	_startX = x;
	_startY = y;
	_angle = angle;
	_speed = speed;
	_isActivate = true;
	_isMoveStart = false;
	_isReady = false;

	_color = color;
	_bulletPatern = patern;
	_moveCount = 0;
	_distance = 0;
	_moveTime = dist;
	_isUp = isUp;
	_bulletSize = size;

	if (_bulletSize == BOSSBULLET_BIG)
	{
		_bulletRC = RectMakeCenter(_x, _y, 30, 30);
		_bulletImage = IMAGEMANAGER->findImage("bigBullet");
	}
	else if(_bulletSize == BOSSBULLET_SMALL)
	{
		_bulletRC = RectMakeCenter(_x, _y, 15, 15);
		_bulletImage = IMAGEMANAGER->findImage("bullet");
	}
	else
	{
		_bulletRC = RectMakeCenter(_x, _y, 8, 8);
		_bulletImage = IMAGEMANAGER->findImage("miniBullet"); 
	}
	return S_OK;
}

void bullet_boss::update(float angle)
{
	switch (_bulletPatern)
	{
	case PATERN1:
		_moveCount++;

		if (_isMoveStart == false)
		{
			if (_moveCount < _moveTime)
			{
				_x += cosf(_angle) * 6.f;
				_y -= sinf(_angle) * 6.f;
				_distance = GetDistance(_x, _y, _startX, _startY);
			}
		}
		else
		{
			/*_x += cosf(_angle) * _speed;
			_y -= sinf(_angle) * _speed;*/

			_x = _startX + cosf(_angle) * _distance;
			_y = _startY - sinf(_angle) * _distance;
			_distance += _speed;
			_angle += 0.004f;

			if (_bulletRC.right < 24- 200 || _bulletRC.left > 505 + 200 || _bulletRC.bottom < 12 - 200 || _bulletRC.top > 575 + 200) _isActivate = false;
		}

		break;
	case PATERN2:

		_x += cosf(_angle) * _speed;
		_y -= sinf(_angle) * _speed;

		if (GetDistance(_x, _y, _startX, _startY) > 30.f)
		{
			_speed += 0.04f;
		}
		
		if (_bulletRC.right < 24 - 200 || _bulletRC.left > 505 + 200 || _bulletRC.bottom < 12 - 200 || _bulletRC.top > 575 + 200) _isActivate = false;

		break;
	case PATERN3:

		_x += cosf(_angle) * _speed;
		_y -= sinf(_angle) * _speed;

		if (GetDistance(_x, _y, _startX, _startY) > 30.f)
		{
			_speed += 0.02f;
		}

		if (_bulletRC.right < 24 - 200 || _bulletRC.left > 505 + 200 || _bulletRC.bottom < 12 - 200 || _bulletRC.top > 575 + 200) _isActivate = false;

		break;
	case PATERN4:

		_x += cosf(_angle) * _speed;
		_y -= sinf(_angle) * _speed;

		if (_bulletRC.right < 24 || _bulletRC.left > 505|| _bulletRC.bottom < 12 || _bulletRC.top > 575) _isActivate = false;

		break;
	case PATERN5:
		_moveCount++;


		if (_isMoveStart == false)
		{
			if (_moveCount < _moveTime)
			{
				_x += cosf(_angle) * 3.f;
				_y -= sinf(_angle) * 3.f;

				_speed = GetDistance(_x, _y, _startX, _startY);
			}
		}
		else
		{
			_x = _startX + cosf(_angle) * _speed;
			_y = _startY - sinf(_angle) * _speed;
			_speed += 1.f;

			_angle += (_isUp == true) ? DEGREE(0.2) : -DEGREE(0.2);

			if (_bulletRC.right < 24 - 200 || _bulletRC.left > 505 + 200 || _bulletRC.bottom < 12 - 200 || _bulletRC.top > 575 + 200) _isActivate = false;
		}
		break;
	case PATERN6:

		_x += cosf(_angle) * 3.f;
		_y -= sinf(_angle) * 3.f;

		if (_bulletRC.right < 24 - 200 || _bulletRC.left > 505 + 200 || _bulletRC.bottom < 12 - 200 || _bulletRC.top > 575 + 200) _isActivate = false;

		break;
	case PATERN7:

		if (_isMoveStart)
		{
			_x += cosf(_angle) * 3.f;
			_y -= sinf(_angle) * 3.f;
		}

		if (_bulletRC.right < 24 || _bulletRC.left > 505 || _bulletRC.bottom < 12 || _bulletRC.top > 575) _isActivate = false;

		break;
	}


	if (_bulletSize == BOSSBULLET_BIG)
	{
		_bulletRC = RectMakeCenter(_x, _y, 30, 30);
	}
	else
	{
		_bulletRC = RectMakeCenter(_x, _y, 15, 15);
	}
}

void bullet_boss::release()
{
}

void bullet_boss::render()
{
	//Rectangle(getMemDC(), _bulletRC);
	/*if (_bulletPatern == PATERN2)
	{
		_bulletImage->frameRender(getMemDC(), _bulletRC.left, _bulletRC.top, _color / 2 , 0);
	}
	else
	{
		_bulletImage->frameRender(getMemDC(), _bulletRC.left, _bulletRC.top, _color, 0);

	}*/

	if (_bulletSize == BOSSBULLET_BIG)
	{
		_bulletImage->frameRender(getMemDC(), _bulletRC.left, _bulletRC.top, _color / 2, 0);
	}
	else if (_bulletSize == BOSSBULLET_SMALL)
	{
		_bulletImage->frameRender(getMemDC(), _bulletRC.left, _bulletRC.top, _color, 0);
	}
	else
	{
		_bulletImage->frameRender(getMemDC(), _bulletRC.left, _bulletRC.top, _color, 0);
	}
}
