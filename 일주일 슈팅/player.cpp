#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "boss.h"
#include "mainGame.h"


HRESULT player::init()
{
	_x = 264;
	_y = 500;
	_speed = 4.f;
	_charNum = 0;
	_frameTime = 0;
	_frameX = 0;

	_playerImage = IMAGEMANAGER->findImage("player");
	_bPower = POWER1;
	_pState = PLAYER_IDLE;
	_alpha = 255;
	_alphaTime = 0;
	_isAlpha = true;
	_playerLife = 3;
	_playerPower = 0;

	_bust1 = { 0,0 };
	_bust2 = { 0,0 };

	for (int i = 0; i < 100; i++)
	{
		bullet_player* _bullet = new bullet_player;
		_bullet->init();
		_qBullet.push(_bullet);
	}

	_minDistance = 0.f;
	_minAngle = 0.f;

	_playerRc = RectMakeCenter(_x , _y, 5, 5);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	
	if (_pState != PLAYER_DIE)
	{
		if (!_isAlpha)
		{
			collisionEnemy();
			collisionBoss();
		}
		keyInput();
		collisionItem();
	}

	if (_playerLife < 0)
	{
		_mg->setScene(RESULTSCENE, 1);
	}
	

	for (_vIBullet = _vBullet.begin(); _vIBullet != _vBullet.end(); ++_vIBullet)
	{
		(*_vIBullet)->update();
	}

	for (int i = 0; i < _vBullet.size();)
	{
		if (_vBullet[i]->getIsActivate() == false)
		{
			pushBullet(_vBullet[i]);
			_vBullet.erase(_vBullet.begin() + i);
		}
		else
		{
			i++;
		}
	}
	animation();


	_playerRc = RectMakeCenter(_x, _y , 5, 5);
}

void player::render()
{

	for (_vIBullet = _vBullet.begin(); _vIBullet != _vBullet.end(); ++_vIBullet)
	{
		
		(*_vIBullet)->render();
	}

	int wid;
	int hei;

	switch (_pState)
	{
	case PLAYER_DIE:
		IMAGEMANAGER->findImage("burst1")->frameRenderCenter(getMemDC(), _x, _y, _bust1.x, _bust1.y);
		IMAGEMANAGER->findImage("burst2")->frameRenderCenter(getMemDC(), _x, _y, _bust2.x, _bust2.y);
		break;
	default:
		if (_isAlpha)
		{
			_playerImage->alphaFrameRender(getMemDC(), _x - _playerImage->getFrameWidth() / 2, _y - _playerImage->getFrameHeight() / 2, _alpha, _frameX, _charNum);
			wid = IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->getWidth();
			hei = IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->getHeight();
			IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->alphaRender(getMemDC(), _x - wid / 2, _y - hei / 2,_alpha);
		}
		else
		{
			_playerImage->frameRender(getMemDC(), _x - _playerImage->getFrameWidth() / 2, _y - _playerImage->getFrameHeight() / 2, _frameX, _charNum);
			wid = IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->getWidth();
			hei = IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->getHeight();
			IMAGEMANAGER->findImage("ÇÇÅºÁ¡")->render(getMemDC(), _x - wid / 2, _y - hei / 2);
		}
		break;
	}


}

void player::collisionEnemy()
{
	if (_em == nullptr) return;
	for (int i = 0; i < _vBullet.size(); i++)
	{
		for (int j = 0; j < _em->getEnemyVector().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_vBullet[i]->getRect(), &_em->getEnemyVector()[j]->getEnemyRect()) &&
				_em->getEnemyVector()[j]->getEnemyState() == IDLE)
			{
				pushBullet(_vBullet[i]);
				_vBullet.erase(_vBullet.begin() + i);
				_em->getEnemyVector()[j]->setEnemyState(DEAD);
				int rnd = GetRandom(100);
				if (rnd < 30)
				{
					itemManager::getInstance()->makeItem(_em->getEnemyVector()[j]->getX(), _em->getEnemyVector()[j]->getY(), ITEM_SMALLPOWERUP);
				}
				else if (rnd < 45)
				{
					itemManager::getInstance()->makeItem(_em->getEnemyVector()[j]->getX(), _em->getEnemyVector()[j]->getY(), ITEM_BIGPOWERUP);
				}
				else if (rnd < 50)
				{
					itemManager::getInstance()->makeItem(_em->getEnemyVector()[j]->getX(), _em->getEnemyVector()[j]->getY(), ITEM_LIFEUP);
				}
				break;
			}
		}
		
	}

	//for (int j = 0; j < _em->getEnemyBullet().size(); j++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_playerRc, &_em->getEnemyBullet()[j]->getRect()))
	//	{
	//		_playerLife--;
	//		_pState = PLAYER_DIE;
	//		_em->removeBullet(j);
	//	}
	//
	//}

	for (_vIBullet = _vBullet.begin(); _vIBullet != _vBullet.end(); ++_vIBullet)
	{
		for (int j = 0; j < _em->getEnemyVector().size();)
		{
			if (_em->getEnemyVector()[j]->getEnemyState() == IDLE)
			{
				(*_vIBullet)->setAngle(GetAngle((*_vIBullet)->getX(), (*_vIBullet)->getY(), _em->getEnemyVector()[j]->getX(), _em->getEnemyVector()[j]->getY()));
				break;
			}
			else if (j + 1 <= _em->getEnemyVector().size())
			{
				j++;

			}
			else
			{
				(*_vIBullet)->setAngle(PI / 2);
				break;
			}
		}
	}
}

void player::collisionBoss()
{
	if (_boss == nullptr) return;

	for (_vIBullet = _vBullet.begin(); _vIBullet != _vBullet.end(); ++_vIBullet)
	{
		(*_vIBullet)->setAngle(GetAngle((*_vIBullet)->getX(), (*_vIBullet)->getY(), _boss->getX(), _boss->getY()));
	}

	for (int i = 0; i < _vBullet.size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_vBullet[i]->getRect(), &_boss->getRect()))
		{
			_boss->setBossHP(1);
			pushBullet(_vBullet[i]);
			_vBullet.erase(_vBullet.begin() + i);
		}
	}

	//for (int i = 0; i < _boss->getTempBullet().size(); i++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_playerRc, &_boss->getTempBullet()[i]->getRect()))
	//	{
	//		_pState = PLAYER_DIE;
	//		_playerLife--;
	//		_boss->removeTempBullet(i);
	//	}
	//}
	//
	//for (int i = 0; i < _boss->getBullet().size(); i++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_playerRc, &_boss->getBullet()[i]->getRect()))
	//	{
	//		_pState = PLAYER_DIE;
	//		_playerLife--;
	//		_boss->removeBullet(i);
	//	}
	//}
}

void player::collisionItem()
{
	for (int i = 0; i < itemManager::getInstance()->getVItem().size(); i++)
	{
		RECT temp;

		float x = itemManager::getInstance()->getVItem()[i]->getX();
		float y = itemManager::getInstance()->getVItem()[i]->getY();

		if (GetDistance(_x, _y, x, y) < 150.f)
		{
			itemManager::getInstance()->getVItem()[i]->setAngle(GetAngle(x, y, _x, _y));
		}

		if (IntersectRect(&temp, &_playerRc, &itemManager::getInstance()->getVItem()[i]->getRect()))
		{
			switch (itemManager::getInstance()->getVItem()[i]->getItemKind())
			{
			case ITEM_SMALLPOWERUP:
				_playerPower += 3;
				if (_playerPower > 120) _playerPower = 120;
				break;
			case ITEM_BIGPOWERUP:
				_playerPower += 12;
				if (_playerPower > 120) _playerPower = 120;
				break;
			case ITEM_LIFEUP:
				_playerLife += 1;
				if (_playerLife > 5) _playerLife = 5;
				break;
			}

			itemManager::getInstance()->popItem(i);
		}
	}
}

void player::animation()
{
	if (_isAlpha)
	{
		_alphaTime++;
		if (_alphaTime > 100)
		{
			_isAlpha = false;
			_alphaTime = 0;
		}

		if (_alphaTime % 5 == 0)
		{
			_alpha = (_alpha == 255) ? 0 : 255;
		}
	}

	switch (_pState)
	{
	case PLAYER_LEFT:
		_frameTime += TIMEMANAGER->getElapsedTime();

		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 10)
			{
				_frameX = 5;
			}
		}
		break;
	case PLAYER_RIGHT:
		_frameTime += TIMEMANAGER->getElapsedTime();

		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 17)
			{
				_frameX = 12;
			}
		}
		break;
	case PLAYER_IDLE:
		_frameTime += TIMEMANAGER->getElapsedTime();

		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;

			_frameX++;

			if (_frameX > 3)
			{
				_frameX = 0;
			}

		}
		break;
	case PLAYER_DIE:

		_frameTime += TIMEMANAGER->getElapsedTime();

		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;

			_bust1.x++;
			_bust2.x++;
			if (_bust2.x > 9)
			{
				_pState = PLAYER_IDLE;
				_bPower = POWER1;
				_x = 264;
				_y = 500;
				_bust1.x = 0;
				_bust2.x = 0;
				_playerPower = 0;

				for (int i = 0; i < _playerPower / 10; i++)
				{
					itemManager::getInstance()->makeItem(GetRandom(150, 400), GetRandom(100, 200), (ITEMKIND)GetRandom(3));
				}

				_isAlpha = true;
			}
		}

		break;
	}
}

void player::makeBullet()
{
	switch (_bPower)
	{
	case POWER1:

		_vBullet.push_back(popBullet(_x-13,_y-30,PI/2));
		_vBullet.push_back(popBullet(_x - 13, _y-30, PI/4,true));
		_vBullet.push_back(popBullet(_x - 13, _y-30, PI/4*3,true));

		if (_playerPower > 30) _bPower = POWER2;

		break;
	case POWER2:

		_vBullet.push_back(popBullet(_x-13-7, _y-30, PI / 2));
		_vBullet.push_back(popBullet(_x-13+7, _y-30, PI / 2));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 4, true));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 4 * 3, true));

		if (_playerPower > 60) _bPower = POWER3;

		break;
	case POWER3:

		_vBullet.push_back(popBullet(_x-13 - 14, _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13  , _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13 + 14, _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13, _y - 30, PI / 4, true));
		_vBullet.push_back(popBullet(_x-13, _y - 30, PI / 4 * 3, true));

		if (_playerPower > 90) _bPower = POWER4;

		break;
	case POWER4:

		_vBullet.push_back(popBullet(_x-13 - 14, _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13, _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13 + 14, _y - 30, PI / 2));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 5, true));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 5*2, true));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 5*4, true));
		_vBullet.push_back(popBullet(_x-13, _y-30, PI / 5*3, true));

		break;
	default:
		break;
	}
}

void player::keyInput()
{
	if (INPUT->GetKey(VK_LEFT) && _pState != PLAYER_DIE)
	{
		if (_x <= 24 + 10)_x = 24;
		else _x -= _speed;

		if (_frameX <= 3) _frameX = 4;
		_pState = PLAYER_LEFT;
	}
	if (INPUT->GetKey(VK_RIGHT) && _pState != PLAYER_DIE)
	{
		if (_x >= 472) _x = 472;
		else _x += _speed;

		if (_frameX <= 11) _frameX = 11;
		_pState = PLAYER_RIGHT;
	}
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		if (_frameX > 3) _frameX = 0;
		_pState = PLAYER_IDLE;
	}
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		if (_frameX > 3) _frameX = 0;
		_pState = PLAYER_IDLE;
	}
	if (INPUT->GetKey(VK_UP))
	{
		if (_y <= 12) _y = 12;
		else _y -= _speed;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		if (_y >= 575 - _playerImage->getFrameHeight()) _y = 575 - _playerImage->getFrameHeight();
		else _y += _speed;
	}
	if (INPUT->GetKey(VK_LSHIFT))
	{
		_speed = 1.5f;
	}
	if (INPUT->GetKeyUp(VK_LSHIFT))
	{
		_speed = 4.f;
	}
	if (INPUT->GetKey('Z'))
	{
		_fireTime += TIMEMANAGER->getElapsedTime();
		if (_fireTime >= 0.2f)
		{
			_fireTime -= 0.2f;
			makeBullet();
		}
		
	}
}

void player::removeBullet(int arr)
{
	delete _vBullet[arr];
	_vBullet.erase(_vBullet.begin() + arr);
}

void player::pushBullet(bullet_player * _bullet)
{
	_bullet->init();
	_qBullet.push(_bullet);
}

bullet_player * player::popBullet(float x, float y, float angle,bool _isHom)
{
	if (_qBullet.size() == 0)
	{
		bullet_player* _bullet = new bullet_player;
		_bullet->init();
		_qBullet.push(_bullet);
	}
	bullet_player* _bullet = _qBullet.front();
	_bullet->init(x, y, angle);
	_bullet->setIsHoming(_isHom,_charNum);
	_qBullet.pop();
	return _bullet;
}
