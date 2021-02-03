#include "stdafx.h"
#include "selectScene.h"
#include "mainGame.h"

HRESULT selectScene::init(mainGame* mg)
{
	_selection = IMAGEMANAGER->findImage("난이도선택");
	_frameX = 0;
	_frameY = 0;
	_isDifficulltySelect = false;
	_isActivate = false;

	_mg = mg;

	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{

	switch (_state)
	{
	case DIFFICULLTYSELECT:
		if (!_isActivate) _isActivate = true;

		if (INPUT->GetKeyDown(VK_UP))
		{
			if (_frameY != 0)
				_frameY--;
		}
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			if (_frameY != 4)
				_frameY++;
		}
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			_state = CHARATERSELECT;
		}

		break;
	case CHARATERSELECT:
		_selection = IMAGEMANAGER->findImage("캐릭터들");

		if (INPUT->GetKeyDown(VK_LEFT))
		{
			if (_frameX != 0) _frameX--;
		}
		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			if (_frameX != 1) _frameX++;
		}
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			_isActivate = false;
			_mg->setScene(PLAYSCENE, _frameX);
			
		}

		break;
	}
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("캐릭선택")->render(getMemDC(), 0, 0);

	switch (_state)
	{
	case DIFFICULLTYSELECT:
		(_frameY == 0) ? _selection->frameRender(getMemDC(), 256, 106, 0, 0) : _selection->frameRender(getMemDC(), 256, 106, 1, 0);
		(_frameY == 1) ? _selection->frameRender(getMemDC(), 355, 187, 0, 1) : _selection->frameRender(getMemDC(), 355, 187, 1, 1);
		(_frameY == 2) ? _selection->frameRender(getMemDC(), 256, 257, 0, 2) : _selection->frameRender(getMemDC(), 256, 257, 1, 2);
		(_frameY == 3) ? _selection->frameRender(getMemDC(), 355, 341, 0, 3) : _selection->frameRender(getMemDC(), 355, 341, 1, 3);
		(_frameY == 4) ? _selection->frameRender(getMemDC(), 256, 401, 0, 4) : _selection->frameRender(getMemDC(), 256, 401, 1, 4);
		break;
	case CHARATERSELECT:
		_selection->frameRender(getMemDC(), 100, 0, _frameX, 0);
		break;
	}

}
