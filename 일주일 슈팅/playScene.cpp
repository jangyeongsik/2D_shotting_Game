#include "stdafx.h"
#include "playScene.h"
#include "mainGame.h"

HRESULT playScene::init(mainGame* mg)
{
	_mg = mg;
	_player.init();
	_isActivate = false;
	_em = new enemyManager;
	_em->init();
	_player.setEnemyManagerAD(_em);

	_player.setMainGameAD(_mg);

	//_boss.init();
	//_boss.setPlayerAD(&_player);
	//_player.setBossAD(&_boss);
	//_boss.setMainGameAD(_mg);

	_pstage = NOMAL;

	itemManager::getInstance()->init(30);


	return S_OK;
}

void playScene::release()
{
}

void playScene::update()
{

	switch (_pstage)
	{
	case NOMAL:
		if (!_isActivate)
		{
			_isActivate = true;
			_player.setCharNum(_mg->getCharNum());
		}
		_player.update();
		_em->update();

		if (_em->getKillCount() > 200)
		{
			_em->getEnemyVector().clear();
			SAFEDELETE(_em);
			_player.setEnemyManagerAD(nullptr);
			_player.setBossAD(&_boss);
			_pstage = BOSS;
			_boss.init();
			_boss.setPlayerAD(&_player);
			_player.setBossAD(&_boss);
			_boss.setMainGameAD(_mg);
		}

		break;
	case BOSS:

		_player.update();
		_boss.update();

		break;
	}

	if (INPUT->GetKeyDown('Q'))
	{
		itemManager::getInstance()->makeItem(200, 200, ITEM_SMALLPOWERUP);
	}
	
	for (int i = 0; i < itemManager::getInstance()->getVItem().size(); i++)
	{
		itemManager::getInstance()->getVItem()[i]->update();
	}

}

void playScene::render()
{
	IMAGEMANAGER->findImage("back")->render(getMemDC(), 24, 12);
	
	if(_pstage == NOMAL) _em->render();
	if(_pstage == BOSS) _boss.render();
	
	_player.render();

	for (int i = 0; i < itemManager::getInstance()->getVItem().size(); i++)
	{
		itemManager::getInstance()->getVItem()[i]->render(getMemDC());
	}

	IMAGEMANAGER->findImage("°ÔÀÓÃ¢")->render(getMemDC(), 0, 0);

	for (int i = 0; i < _player.getPlayerLife(); i++)
	{
		IMAGEMANAGER->findImage("redStar")->render(getMemDC(), 584 + (i * 20), 162);
	}

	if (_player.getPlayerPower() != 120)
	{
		for (int i = 1, di = 0; i <= _player.getPlayerPower(); i *= 10)
		{
			int num = (_player.getPlayerPower() / i) % 10;
			IMAGEMANAGER->findImage("numbers")->frameRender(getMemDC(), 610 - (di * 13), 112, num, 0);
			di++;
		}
	}
	else
	{
		IMAGEMANAGER->findImage("max")->render(getMemDC(),590, 112);
	}
	
}


