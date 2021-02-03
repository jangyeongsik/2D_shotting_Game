#pragma once

enum ITEMKIND
{
	ITEM_SMALLPOWERUP,
	ITEM_BIGPOWERUP,
	ITEM_LIFEUP,
	ITEM_EMPTY
};

class item
{
private:
	float _x, _y;
	float _gravity;
	float _angle;
	float _speed;

	RECT _rc;
	ITEMKIND _kind;

public:
	item() {}
	~item() {}

	HRESULT init();
	HRESULT init(float x, float y, ITEMKIND kind);
	void update();
	void render(HDC hdc);
	void setAngle(float angle) { _angle = angle; _gravity = 0; _speed = 7.f; }
	RECT getRect() { return _rc; }
	ITEMKIND getItemKind() { return _kind; }
	float getX() { return _x; }
	float getY() { return _y; }
};
