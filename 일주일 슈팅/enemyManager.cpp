#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{

	_redEnemySetPos = GetRandom(100, 200);
	_blueSetCount = 5;


	for (int i = 0; i < 300; i++)
	{
		bullet_enemy* _eb = new bullet_enemy;
		_eb->init();
		_qBullet.push(_eb);
	}

	_enemyKillCount = 0;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	_redEnemySetTime++;
	_blueEnemySetTime++;
	updateBullet();

	if (_redEnemySetTime >= 200)
	{
		setRecEnemy();
		_redEnemySetTime = 0;
	}

	if (_blueEnemySetTime > 250)
	{
		setBlueEnemy();
	}
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();

		if (_vEnemy[i]->getEnemyKind() == RED)
		{
			if (_vEnemy[i]->getFireCount() % 60 == 0 && _vEnemy[i]->getEnemyState() == IDLE)
			{
				pushBullet(_vEnemy[i]->getX(), _vEnemy[i]->getY(), -PI / 2);
			}
		}
		if (_vEnemy[i]->getEnemyKind() == BLUE)
		{
			if (_vEnemy[i]->getFireCount() % 30 == 0 && _vEnemy[i]->getEnemyState() == IDLE)
			{
				pushBullet(_vEnemy[i]->getX(), _vEnemy[i]->getY(), -PI / 4);
				pushBullet(_vEnemy[i]->getX(), _vEnemy[i]->getY(), -PI / 4 * 3);
				pushBullet(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI / 4);
				pushBullet(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI / 4 * 3);
			}
		}

	}


	for (int i = 0; i < _vEnemy.size();)
	{
		if (_vEnemy[i]->getIsActivate() == false)
		{
			removeEnemy(i);
		}
		else
		{
			++i;
		}
	}
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i]->render();
	}
}

void enemyManager::setRecEnemy()
{
	bool _isLeft = GetRandom(2);

	for (int i = 0; i < 10; i++)
	{
		enemy* _en = new enemy_red;
		dynamic_cast<enemy_red*>(_en)->init(_isLeft, i * 30, _redEnemySetPos);
		_vEnemy.push_back(_en);
	}
	for (int i = 0; i < 10; i++)
	{
		enemy* _en = new enemy_red;
		dynamic_cast<enemy_red*>(_en)->init(_isLeft, i * 30, _redEnemySetPos+50);
		_vEnemy.push_back(_en);
	}
}

void enemyManager::setBlueEnemy()
{
	bool _isLeft = GetRandom(2);
	if (_blueEnemySetTime % 20 == 0)
	{
		if (_blueSetCount > 0)
		{
			enemy* _en = new enemy_blue;
			dynamic_cast<enemy_blue*>(_en)->init(_isLeft);
			_vEnemy.push_back(_en);
			_blueSetCount--;
		}
		else
		{
			_blueSetCount = 5;
			_blueEnemySetTime = 0;
		}
	}
}

void enemyManager::updateBullet()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i]->update();
	}

	for (int i = 0; i < _vBullet.size();)
	{
		if (_vBullet[i]->getIsActivate() == false)
		{
			popBullet(_vBullet[i]);
			_vBullet.erase(_vBullet.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void enemyManager::pushBullet(float x, float y, float angle)
{
	bullet_enemy* _bullet = _qBullet.front();
	_qBullet.pop();
	_bullet->init(x, y, angle);
	_vBullet.push_back(_bullet);
}

void enemyManager::popBullet(bullet_enemy * eb)
{
	eb->init();
	_qBullet.push(eb);
}

void enemyManager::removeEnemy(int arr)
{
	delete _vEnemy[arr];
	_vEnemy.erase(_vEnemy.begin() + arr);
	_enemyKillCount++;
}

void enemyManager::removeBullet(int arr)
{
	_vBullet[arr]->init();
	_qBullet.push(_vBullet[arr]);
	_vBullet.erase(_vBullet.begin() + arr);
}
