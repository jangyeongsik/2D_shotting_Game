#include "stdafx.h"
#include "mainScene.h"
#include "mainGame.h"

HRESULT mainScene::init(mainGame* mg)
{
	_mg = mg;
	_frameX = 0;
	_isActivate = false;

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	if (!_isActivate) _isActivate = true;
	if (INPUT->GetKeyDown(VK_SPACE))
	{
		_isActivate = false;
		_mg->setScene(SELECTSCENE);
	}
}

void mainScene::render()
{
	IMAGEMANAGER->findImage("Å¸ÀÌÆ²")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("start")->frameRender(getMemDC(), WINSIZEX / 2 - 300, WINSIZEY / 2+50,0,0);
}
