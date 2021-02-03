#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	_x = 0;
	_y = 0;
	_gravity = 0.f;
	_angle = 0.f;
	_kind = ITEM_EMPTY;
	_rc = RectMakeCenter(_x, _y, 16, 16);
	_speed = 0.f;
	return S_OK;
}

HRESULT item::init(float x, float y, ITEMKIND kind)
{

	_x = x;
	_y = y;
	_gravity = 0.f;
	_kind = kind;
	_angle = PI / 2;
	_speed = 2.f;

	if (_kind == ITEM_SMALLPOWERUP) _rc = RectMakeCenter(_x, _y, 12, 12);
	else _rc = RectMakeCenter(_x, _y, 16, 16);

	return S_OK;
}

void item::update()
{
	_gravity -= 0.02f;
	_y -= sinf(_angle) * _speed  + _gravity;
	_x += cosf(_angle) * _speed;

	if (_kind == ITEM_SMALLPOWERUP) _rc = RectMakeCenter(_x, _y, 12, 12);
	else _rc = RectMakeCenter(_x, _y, 16, 16);
}

void item::render(HDC hdc)
{
	Rectangle(hdc, _rc);

	switch (_kind)
	{
	case ITEM_SMALLPOWERUP:
		IMAGEMANAGER->findImage("item")->frameRenderCenter(hdc, _x, _y, 0, 0);
		break;
	case ITEM_BIGPOWERUP:
		IMAGEMANAGER->findImage("item")->frameRenderCenter(hdc, _x, _y, 1, 0);
		break;
	case ITEM_LIFEUP:
		IMAGEMANAGER->findImage("item")->frameRenderCenter(hdc, _x, _y, 2, 0);
		break;
	}
}
