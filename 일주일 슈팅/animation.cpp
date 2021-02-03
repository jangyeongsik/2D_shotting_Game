#include "stdafx.h"
#include "animation.h"

HRESULT animation::init(image * ig, bool isLoop, bool isReverse)
{
	_maxFrameX = ig->getMaxFrameX();
	_maxFrameY = ig->getMaxFrameY();
	_frameWidth = ig->getFrameWidth();
	_FrameHeight = ig->getFrameHeight();
	_frameX = 0;
	_frameY = 0;

	_isLoop = isLoop;
	_isReverse = isReverse;

	_time = 0.0f;

	return S_OK;
}

void animation::frameUpdate()
{
	_time += TIMEMANAGER->getElapsedTime();

	if (_isRender)
	{
		if (_time > _renderSpeed)
		{
			_time -= _renderSpeed;

			_frameX++;
			if (_frameX > _maxFrameX)
			{
				if (_isLoop) _frameX = 0;
				else
				{
					_frameX = 0;
					_isRender = false;
				}
			}

		}
	}


}

void animation::render(HDC hdc, image * ig)
{
	if (_isRender)
	{
		ig->frameRender(hdc, _destX, _destY, _frameX, _frameY);
	}
}

void animation::render(HDC hdc,image* ig,int destX, int destY)
{
	if (_isRender)
	{
		ig->frameRender(hdc, destX, destY, _frameX, _frameY);
	}
}

void animation::setRenderSpeed(float speed)
{
	_renderSpeed = 1.0f / speed;
}
