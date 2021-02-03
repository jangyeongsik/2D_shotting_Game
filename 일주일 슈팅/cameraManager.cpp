#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY)
{
	_maxX = maxX;
	_maxY = maxY;
	_minX = minX;
	_minY = minY;
	_pivotX = pivotX;
	_pivotY = pivotY;
	_distanceX = disX;
	_distanceY = disY;
	_absDistanceX = disX;
	_absDistanceY = disY;
	
	_cameraRect = RectMake(_pivotX - disX, _pivotY - disY, WINSIZEX, WINSIZEY);


	return S_OK;
}

void cameraManager::Rectangle(HDC hdc, RECT rc)
{
	::Rectangle(hdc,getRelativeX(rc.left), getRelativeY(rc.top),getRelativeX(rc.right),getRelativeY(rc.bottom));
}

void cameraManager::Rectangle(HDC hdc, int left, int top, int width, int height)
{
}

void cameraManager::Render(HDC hdc, image* ig, int destX, int destY)
{
	ig->render(hdc, getRelativeX(destX), getRelativeY(destY));
}

void cameraManager::movePivot(float &x, float &y)
{
	if (_isControl == false)
	{
		_pivotX = x;
		_pivotY = y;
		_cameraRect = RectMake(_pivotX - _absDistanceX, _pivotY - _absDistanceY, WINSIZEX, WINSIZEY);

		if (_cameraRect.left <= _minX)
		{
			_cameraRect.left = _minX;
			_cameraRect.right = _minX + WINSIZEX;
			_distanceX = _pivotX - _cameraRect.left;
		}
		if (_cameraRect.right >= _maxX)
		{
			_cameraRect.right = _maxX;
			_cameraRect.left = _maxX - WINSIZEX;
			_distanceX = _pivotX - _cameraRect.left;
		}
		if (_cameraRect.top <= _minY)
		{
			_cameraRect.top = _minY;
			_cameraRect.bottom = _minY - WINSIZEY;
			_distanceY = _pivotY - _cameraRect.top;
		}
		if (_cameraRect.bottom >= _maxY)
		{
			_cameraRect.bottom = _maxY;
			_cameraRect.top = _maxY - WINSIZEY;
			_distanceY = _pivotY - _cameraRect.top;
		}
	}
	

}

int cameraManager::getRelativeX(float x)
{
	return x - _cameraRect.left;
}

int cameraManager::getRelativeY(float y)
{
	return y - _cameraRect.top;
}
