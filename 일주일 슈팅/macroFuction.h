#pragma once

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}
inline RECT RectMake(int left, int top, int width, int height)
{
	RECT rc = { left, top,left + width,top + height };
	return rc;
}
inline void LineMake(HDC hdc, int startx, int starty, int endx, int endy)
{
	MoveToEx(hdc, startx, starty, NULL);
	LineTo(hdc, endx, endy);
}
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
inline void RectangleMake(HDC hdc, int left, int top, int wid, int height)
{
	Rectangle(hdc, left, top, left + wid, top + height);
}
inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline int GetRandom(int num)
{
	return rand() % num;
}
inline int GetRandom(int from, int to)
{
	return rand() % (to - from) + from;
}
inline float GetRandom(float num)
{
	return (float)rand() / num;
}
inline float GetRandom(float from, float to)
{
	float rnd = (float)rand() / (float)RAND_MAX;
	return (rnd * (to - from) + from);
}

inline float GetDistance(float x1, float y1, float x2, float y2)
{
	float w = x2 - x1;
	float h = y2 - y1;
	float r = sqrt((w * w) + (h * h));
	return r;
}

inline float GetAngle(float x1, float y1, float x2, float y2)
{
	return -atan2( y2 - y1, x2 - x1);
}