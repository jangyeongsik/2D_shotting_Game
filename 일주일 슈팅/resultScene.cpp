#include "stdafx.h"
#include "resultScene.h"
#include "mainGame.h"

HRESULT resultScene::init(mainGame* mg)
{
	_mg = mg;
	_alpha = 0;

	return S_OK;
}

void resultScene::release()
{
}

void resultScene::update()
{
	_alpha++;
	if (_alpha > 255) _alpha = 255;
}

void resultScene::render()
{
	IMAGEMANAGER->findImage("logoBig")->alphaFrameRender(getMemDC(), 170, 0, _alpha, _mg->getCharNum(), 0);
}
