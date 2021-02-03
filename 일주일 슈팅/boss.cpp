#include "stdafx.h"
#include "boss.h"
#include "player.h"
#include "mainGame.h"

HRESULT boss::init()
{
	_x = 280;
	_y = 0;
	
	_movePoint = { 0,0 };
	_moveTime = 0;
	
	_bossState = BOSS_INIT;
	_angle = PI / 2;
	_frameTime = 0.f;
	_frameX = _frameY = 0;

	_bossPhase = BOSS_PHASE1;

	_isFire = false;

	for (int i = 0; i < 1000; i++)
	{
		bullet_boss* _bullet = new bullet_boss;
		_bullet->init();
		_qBullet.push(_bullet);
	}

	_offsetY = 0;

	_bossHp = 1000;
	
	//_patern = GetRandom(6)+1;
	_patern = 1;
	_bossImage = IMAGEMANAGER->findImage("케이네");
	_bulletColor = GetRandom(16);
	_bulletColor2 = GetRandom(16);

	_bossRC = RectMakeCenter(_x, _y, _bossImage->getFrameWidth(), _bossImage->getFrameHeight());

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	move();
	setBossPhase();
	animation();


	updateBullet();

	_bossRC = RectMakeCenter(_x, _y, _bossImage->getFrameWidth()-15, _bossImage->getFrameHeight());
}

void boss::render()
{
	if (_bossState == BOSS_SKILL)
	{
		RECT rc = { 24,12,505,575 };
		IMAGEMANAGER->findImage("스킬배경2")->loopRender(getMemDC(),&rc , 0,_offsetY);
	}

	IMAGEMANAGER->addImage("buf", WINSIZEX, WINSIZEY);
	this->getBackBuffer()->render(IMAGEMANAGER->findImage("buf")->getHDC(), 0, 0);
	IMAGEMANAGER->findImage("bossHp")->strechRender(IMAGEMANAGER->findImage("buf")->getHDC(), 24, 12, 480, 16);
	IMAGEMANAGER->findImage("buf")->render(getMemDC(), 24, 12, 24, 12, (480.f / 1000.f)*_bossHp, 16);

	//Rectangle(getMemDC(), _bossRC);
	_bossImage->frameRender(getMemDC(), _bossRC.left-7, _bossRC.top, _frameX, _frameY);
	//RectangleMake(getMemDC(), _movePoint.x, _movePoint.y, 10, 10);

	renderBullet();

	/*char temp[128];
	wsprintf(temp, "qB : %d", _qBullet.size());
	TextOut(getMemDC(), 50, 10, temp, strlen(temp));
	wsprintf(temp, "vB : %d", _vBullet.size());
	TextOut(getMemDC(), 50, 30, temp, strlen(temp));
	wsprintf(temp, "tB : %d", _tempBullet.size());
	TextOut(getMemDC(), 50, 50, temp, strlen(temp));
	wsprintf(temp, "total : %d", _tempBullet.size() + _qBullet.size() + _vBullet.size());
	TextOut(getMemDC(), 50, 70, temp, strlen(temp));
	wsprintf(temp, "hp : %d",_bossHp);
	TextOut(getMemDC(), 50, 90, temp, strlen(temp));
	wsprintf(temp, "state : %d", _bossState);
	TextOut(getMemDC(), 50, 110, temp, strlen(temp));
	wsprintf(temp, "phase : %d", _bossPhase);
	TextOut(getMemDC(), 50, 130, temp, strlen(temp));
	wsprintf(temp, "frameX : %d", _frameX);
	TextOut(getMemDC(), 50, 150, temp, strlen(temp));
	wsprintf(temp, "frameY : %d", _frameY);
	TextOut(getMemDC(), 50, 170, temp, strlen(temp));*/
}

void boss::animation()
{
	switch (_bossState)
	{
	case BOSS_LEFT:
		_frameY = 2;
		_frameTime += TIMEMANAGER->getElapsedTime();
		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 3)
			{
				_frameX = 1;
			}
		}
		break;
	case BOSS_RIGHT:
		_frameY = 1;
		_frameTime += TIMEMANAGER->getElapsedTime();
		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 3)
			{
				_frameX = 1;
			}
		}
		break;
	case BOSS_INIT:
	case BOSS_IDLE:
		_frameY = 0;
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
	case BOSS_SKILL:
		_frameY = 3;
		_frameTime += TIMEMANAGER->getElapsedTime();
		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 3)
			{
				_frameX = 3;
			}
		}
		break;
	case BOSS_DEAD:
		_frameTime += TIMEMANAGER->getElapsedTime();
		if (_frameTime > 0.1f)
		{
			_frameTime -= 0.1f;
			_frameX++;
			if (_frameX > 10)
			{
				_mg->setScene(RESULTSCENE, 0);
			}
		}
		break;
	}

	

}

void boss::move()
{

	switch (_bossState)
	{
	case BOSS_LEFT:
		
		if (GetDistance(_x, _y, _movePoint.x, _movePoint.y) < 2.f)
		{
			if (_bossHp < 400 && _bossPhase == BOSS_PHASE1)
			{
				_bossState = BOSS_SKILL;
				_bossPhase = BOSS_PHASE2;
				_patern = 4;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}

			else if (GetRandom(20) == 0)
			{
				_bossState = BOSS_SKILL;
				_patern = 4;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}
			else
			{
				_bossState = BOSS_IDLE;
				_patern = GetRandom(6) + 1;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}
			
		}
		else
		{
			_angle = GetAngle(_x, _y, _movePoint.x, _movePoint.y);
			_x += cosf(_angle) * 3.f;
			_y -= sinf(_angle) * 3.f;
		}
		break;
	case BOSS_RIGHT:
		

		if (GetDistance(_x, _y, _movePoint.x, _movePoint.y) < 2.f)
		{
			if (_bossHp < 400 && _bossPhase == BOSS_PHASE1)
			{
				_bossState = BOSS_SKILL;
				_bossPhase = BOSS_PHASE2;
				_patern = 4;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}

			else if (GetRandom(20) == 0)
			{
				_bossState = BOSS_SKILL;
				_patern = 4;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}
			else
			{
				_bossState = BOSS_IDLE;
				_patern = GetRandom(6
				) + 1;
				_bulletColor = GetRandom(16);
				_bulletColor2 = GetRandom(16);
				_isFire = false;
			}
		}
		else
		{
			_angle = GetAngle(_x, _y, _movePoint.x, _movePoint.y);
			_x += cosf(_angle) * 3.f;
			_y -= sinf(_angle) * 3.f;
		}

		break;
	case BOSS_IDLE:

		if (_isFire == true)
		{
			
			_moveTime++;

			if (_moveTime > 70)
			{
				_movePoint.x = GetRandom(50, 470);
				_movePoint.y = GetRandom(50, 300);
				_moveTime = 0;
				_fireTime = 0;

				if (_movePoint.x > _x)
				{
					_bossState = BOSS_RIGHT;
				}
				else
				{
					_bossState = BOSS_LEFT;
				}
			}
		}
		else
		{
			_fireTime++;

			switch (_patern)
			{
			case 1:
				setPatern1();
				break;
			case 2:
				setPatern2();
				break;
			case 3:
				setPatern3();
				break;
			case 4:
				setPatern5();
				break;
			case 5:
				setPatern6();
				break;
			case 6:
				setPatern7();
				break;
			}
		}

		break;
	case BOSS_SKILL:

		_offsetY--;
		if (_offsetY < -1126) _offsetY = 0;
		
		if (GetDistance(_x, _y, 280, 200) >= 2.f)
		{
			_angle = GetAngle(_x, _y, 280, 200);
			_x += cosf(_angle) *3.f;
			_y -= sinf(_angle) * 3.f;
		}
		else
		{
			_x = 280;
			_y = 200;
			_fireTime++;
			setPatern4();
		}

		break;
	case BOSS_INIT:
		_y += 2.f;

		if (_y > 200)
		{
			_bossState = BOSS_IDLE;
		}
		break;
	default:
		break;
	}
	if (_bossHp < 0 && _bossState != BOSS_DEAD)
	{
		_bossState = BOSS_DEAD;
		_bossImage = IMAGEMANAGER->findImage("bossDead");
		_frameY = 0;
		_frameX = 0;
		while (!_tempBullet.empty())
		{
			removeTempBullet(0);
		}
		while (!_vBullet.empty())
		{
			removeBullet(0);
		}
	}

}

void boss::setBossPhase()
{
	
}



void boss::makeBullet(float x, float y, float angle, float speed, BOSSBULLETSIZE size, BOSSBULLETPATERN patern, int color, bool isUP, float dist)
{
	if (_qBullet.size() == 0)
	{
		bullet_boss* _bullet = new bullet_boss;
		_bullet->init();
		_qBullet.push(_bullet);
	}
	bullet_boss* _bullet = _qBullet.front();
	_bullet->init(x, y, angle, speed, size, patern, color, isUP,dist);
	_qBullet.pop();
	_tempBullet.push_back(_bullet);
}

void boss::removeBullet(int arr)
{
	_vBullet[arr]->init();
	_qBullet.push(_vBullet[arr]);
	_vBullet.erase(_vBullet.begin() + arr); 
}

void boss::removeTempBullet(int arr)
{
	_tempBullet[arr]->init();
	_qBullet.push(_tempBullet[arr]);
	_tempBullet.erase(_tempBullet.begin() + arr);
}

bool boss::setPatern1()
{

	if (_bossPhase == BOSS_PHASE1)
	{
		if (_fireTime >= 2 && _fireTime <= 106)
		{
			if (_fireTime % 2 == 0)
			{
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor,false, 5.f);
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor2,false, 10.f);
			}
		}
		if (_fireTime > 116)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}

	if (_bossPhase == BOSS_PHASE2)
	{
		if (_fireTime >= 2 && _fireTime <= 106)
		{
			if (_fireTime % 2 == 0)
			{
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor, false, 6.f);
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor2, false, 9.f);
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor, false, 12.f);
				makeBullet(_x, _y, DEGREE(360 / 50 * (_fireTime / 2) + 250), 1.5f + (_fireTime / 5.f * 0.05f), BOSSBULLET_SMALL, PATERN1, _bulletColor2, false, 3.f);
			}
		}
		if (_fireTime > 116)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}
	
	return false;
}

bool boss::setPatern2()
{
	if (_bossPhase == BOSS_PHASE1)
	{
		if ((_fireTime > 20 && _fireTime <= 35) ||
			(_fireTime > 40 && _fireTime <= 55) ||
			(_fireTime > 60 && _fireTime <= 75))
		{
			if (_fireTime % 3 == 0)
			{
				makeBullet(_x - 8, _y, GetAngle(_x, _y, _player->getX(), _player->getY()), 1.5f,BOSSBULLET_SMALL, PATERN2, _bulletColor);
				makeBullet(_x + 8, _y, GetAngle(_x, _y, _player->getX(), _player->getY()), 1.5f, BOSSBULLET_SMALL, PATERN2, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}
		}
		if (_fireTime > 75)
		{
			_isFire = true;
			return true;
		}
	}

	else
	{
		if ((_fireTime > 30 && _fireTime <= 48) ||
			(_fireTime > 55 && _fireTime <= 73) ||
			(_fireTime > 80 && _fireTime <= 98))
		{
			if (_fireTime % 6 == 0)
			{
				makeBullet(_x - 16, _y, GetAngle(_x, _y, _player->getX(), _player->getY()), 1.5f, BOSSBULLET_BIG, PATERN2, _bulletColor);
				makeBullet(_x + 16, _y, GetAngle(_x, _y, _player->getX(), _player->getY()), 1.5f, BOSSBULLET_BIG, PATERN2, _bulletColor);
			}
		}

		if (_fireTime > 150)
		{
			_isFire = true;

			while (!_tempBullet.empty())
			{
				for (int i = 0; i < 15; i++)
				{
					makeBullet(_tempBullet.back()->getX(), _tempBullet.back()->getY(), DEGREE(360 / 15 * i + GetRandom(360)), 1.5f, BOSSBULLET_SMALL, PATERN4, _bulletColor);
					_vBullet.push_back(_tempBullet.back());
					_tempBullet.pop_back();
				}
				_tempBullet.pop_back();
			}

			return true;
		}
	}

	return false;
}

bool boss::setPatern3()
{
	if (_bossPhase == BOSS_PHASE1)
	{
		if (_fireTime >= 30 && _fireTime <= 60)
		{
			if (_fireTime % 10 == 0)
			{
				if ((_fireTime / 10) % 2 == 0)
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 0.5f, BOSSBULLET_SMALL, PATERN3, _bulletColor);
						_vBullet.push_back(_tempBullet.back());
						_tempBullet.pop_back();
					}
				}
				else
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i + 20), 0.5f, BOSSBULLET_SMALL, PATERN3, _bulletColor2);
						_vBullet.push_back(_tempBullet.back());
						_tempBullet.pop_back();
					}
				}
			}

		}
		if (_fireTime > 60)
		{
			_isFire = true;
			return true;
		}
	}

	else
	{
		if (_fireTime >= 30 && _fireTime <= 60)
		{
			if (_fireTime % 10 == 0)
			{
				if ((_fireTime / 10) % 2 == 0)
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 0.5f, BOSSBULLET_SMALL, PATERN3, _bulletColor);
						_vBullet.push_back(_tempBullet.back());
						_tempBullet.pop_back();
					}
				}
				else
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i + 20), 0.5f, BOSSBULLET_SMALL, PATERN3, _bulletColor2);
						_vBullet.push_back(_tempBullet.back());
						_tempBullet.pop_back();
					}
				}
			}

		}
		if (_fireTime > 60 && _fireTime <= 90)
		{
			if (_fireTime % 10 == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					makeBullet(_x, _y, DEGREE(360 / 10 * i), 0.5f, BOSSBULLET_BIG, PATERN3, _bulletColor);
					_vBullet.push_back(_tempBullet.back());
					_tempBullet.pop_back();
				}
			}
		}
		if (_fireTime > 90)
		{
			_isFire = true;
			return true;
		}
	}
	
	return false;
}


static float _fireAngle = 280;
bool boss::setPatern4()
{
	
	if (_fireTime >= 50 && _fireTime <= 1000)
	{
		if (_fireTime % 10 == 0)
		{
			if (_fireTime / 10 == 5)
			{
				_fireAngle = 280;
			}
			for (int i = 0; i < 50; i++)
			{
				makeBullet(_x, _y, DEGREE((360 / 51 * i) + _fireAngle), 2.f, BOSSBULLET_SMALL, PATERN4, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}
			if(_fireTime/10 < GetRandom(14,16))  _fireAngle += 3;
			else if (_fireTime/10 < GetRandom(36,39)) _fireAngle -= 3;
			else if (_fireTime/10 < GetRandom(58,61)) _fireAngle +=3;
			else if (_fireTime/10 < GetRandom(77,80)) _fireAngle -=3;
			else if (_fireTime/10 < 100) _fireAngle += 3;
			
		}
	}
	if (_fireTime > 1000)
	{
		_isFire = true;
		_bossState = BOSS_IDLE;
		return true;
	}
	return false;
}

bool boss::setPatern5()
{
	if (_bossPhase == BOSS_PHASE1)
	{
		if (_fireTime >= 40 && _fireTime < 80)
		{
			if (_fireTime % 20 == 0)
			{

				if (_fireTime / 20 == 2)
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 2.f, BOSSBULLET_SMALL, PATERN5, _bulletColor, false,30.f);
					}
				}
				else
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 2.f, BOSSBULLET_SMALL, PATERN5, _bulletColor, true,15.f);
					}
				}
			}
		}

		if (_fireTime > 80)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}
	else
	{
		if (_fireTime >= 40 && _fireTime < 160)
		{
			if (_fireTime % 20 == 0)
			{

				if (_fireTime / 20 % 2 == 0)
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 2.f, BOSSBULLET_SMALL, PATERN5, _bulletColor, false, 10.f + (_fireTime / 20.f * 9.f));
					}
				}
				else
				{
					for (int i = 0; i < 30; i++)
					{
						makeBullet(_x, _y, DEGREE(360 / 30 * i), 2.f, BOSSBULLET_SMALL, PATERN5, _bulletColor2, true, 10.f + (_fireTime / 20.f * 9.f));
					}
				}
			}
		}

		if (_fireTime > 220)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}
	
	return false;
}

static float _sixAngle = 0;

bool boss::setPatern6()
{

	if (_bossPhase == BOSS_PHASE1)
	{
		if (_fireTime >= 40 && _fireTime < 140)
		{
			if (_fireTime % 10 == 0)
			{
				float x = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				float y = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;
				float x2 = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				float y2 = y - sinf(DEGREE(216) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(216) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(288) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(288) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(0) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(0) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(72) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(72) + _sixAngle) * 40.f;
				x2 = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				y2 = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				_sixAngle += 0.1;
			}
		}

		if (_fireTime >= 150 && _fireTime < 250)
		{
			if (_fireTime % 10 == 0)
			{
				float x = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				float y = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;
				float x2 = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				float y2 = y - sinf(DEGREE(216) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(216) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(288) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(288) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(0) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(0) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(72) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(72) + _sixAngle) * 40.f;
				x2 = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				y2 = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				_sixAngle -= 0.1;
			}
		}
		if (_fireTime > 280)
		{
			_isFire = true;
			return true;
		}
	}

	else
	{
		if (_fireTime >= 40 && _fireTime < 140)
		{
			if (_fireTime % 10 == 0)
			{
				float x = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				float y = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;
				float x2 = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				float y2 = y - sinf(DEGREE(216) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(216) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(288) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(288) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(0) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(0) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(72) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(72) + _sixAngle) * 40.f;
				x2 = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				y2 = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				for (int i = 0; i < 20; i++)
				{
					makeBullet(_x, _y, DEGREE(360 / 20 * i), 2.f, BOSSBULLET_SMALL, PATERN5, _bulletColor2, false);
					_tempBullet.back()->setIsMove(true);
					_vBullet.push_back(_tempBullet.back());
					_tempBullet.pop_back();
				}

				_sixAngle += 0.1;
			}
		}

		if (_fireTime >= 150 && _fireTime < 250)
		{

			if (_fireTime % 10 == 0)
			{
				float x = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				float y = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;
				float x2 = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				float y2 = y - sinf(DEGREE(216) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(216) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(216) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(288) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(288) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(288) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(0) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(0) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(0) + _sixAngle) * 40.f;
				x2 = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y2 = y - sinf(DEGREE(72) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				x = x + cosf(DEGREE(72) + _sixAngle) * 40.f;
				y = y - sinf(DEGREE(72) + _sixAngle) * 40.f;
				x2 = _x + cosf(DEGREE(90) + _sixAngle) * 40.f;
				y2 = _y - sinf(DEGREE(90) + _sixAngle) * 40.f;

				makeBullet(x, y, GetAngle(x, y, x2, y2), 1.f, BOSSBULLET_SMALL, PATERN6, _bulletColor);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();

				_sixAngle -= 0.1;
			}
		}
		if (_fireTime > 280)
		{
			_isFire = true;
			return true;
		}
	}
	
	return false;
}

static int randomAngle = GetRandom(5) + 3;
bool boss::setPatern7()
{	
	if (_bossPhase == BOSS_PHASE1)
	{
		if (_fireTime > 50 && _fireTime <= 100)
		{
			if (_fireTime % 10 == 0)
			{
				switch (_fireTime / 10)
				{
				case 6:
					setStar(_x + cosf(DEGREE(90)) * 80.f , _y - sinf(DEGREE(90)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					_bulletColor = GetRandom(16);
					break;
				case 7:
					setStar(_x + cosf(DEGREE(12)) * 80.f, _y - sinf(DEGREE(12)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					_bulletColor = GetRandom(16);
					break;
				case 8:
					setStar(_x + cosf(DEGREE(168)) * 80.f, _y - sinf(DEGREE(168)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					_bulletColor = GetRandom(16);
					break;
				case 9:
					setStar(_x + cosf(DEGREE(240)) * 80.f, _y - sinf(DEGREE(240)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					_bulletColor = GetRandom(16);
					break;
				case 10:
					setStar(_x + cosf(DEGREE(300)) * 80.f, _y - sinf(DEGREE(300)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					_bulletColor = GetRandom(16);
					break;
				}
			}
		}

		if (_fireTime > 100)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}
	else
	{
		if (_fireTime > 50 && _fireTime <= 100)
		{
			if (_fireTime % 10 == 0)
			{
				switch (_fireTime / 10)
				{
				case 6:
					setStar(_x + cosf(DEGREE(90) + DEGREE(180)) * 80.f, _y - sinf(DEGREE(90) + DEGREE(180)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					setStar(_x + cosf(DEGREE(90)) * 150.f, _y - sinf(DEGREE(90)) * 150.f, 0, 80.f, BOSSBULLET_SMALL, _bulletColor2);
					_bulletColor = GetRandom(16);
					_bulletColor2 = GetRandom(16);
					break;
				case 7:
					setStar(_x + cosf(DEGREE(12) + DEGREE(180)) * 80.f, _y - sinf(DEGREE(12) + DEGREE(180)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					setStar(_x + cosf(DEGREE(12)) * 150.f, _y - sinf(DEGREE(12)) * 150.f, 0, 80.f, BOSSBULLET_SMALL, _bulletColor2);
					_bulletColor = GetRandom(16);
					_bulletColor2 = GetRandom(16);
					break;
				case 8:
					setStar(_x + cosf(DEGREE(168) + DEGREE(180)) * 80.f, _y - sinf(DEGREE(168) + DEGREE(180)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					setStar(_x + cosf(DEGREE(168)) * 150.f, _y - sinf(DEGREE(168)) * 150.f, 0, 80.f, BOSSBULLET_SMALL, _bulletColor2);
					_bulletColor = GetRandom(16);
					_bulletColor2 = GetRandom(16);
					break;
				case 9:
					setStar(_x + cosf(DEGREE(240) + DEGREE(180)) * 80.f, _y - sinf(DEGREE(240) + DEGREE(180)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					setStar(_x + cosf(DEGREE(240)) * 150.f, _y - sinf(DEGREE(240)) * 150.f, 0, 80.f, BOSSBULLET_SMALL, _bulletColor2);
					_bulletColor = GetRandom(16);
					_bulletColor2 = GetRandom(16);
					break;
				case 10:
					setStar(_x + cosf(DEGREE(300) + DEGREE(180)) * 80.f, _y - sinf(DEGREE(300) + DEGREE(180)) * 80.f, 0, 50.f, BOSSBULLET_MINI, _bulletColor);
					setStar(_x + cosf(DEGREE(300)) * 150.f, _y - sinf(DEGREE(300)) * 150.f, 0, 80.f, BOSSBULLET_SMALL, _bulletColor2);
					_bulletColor = GetRandom(16);
					_bulletColor2 = GetRandom(16);
					break;
				}
			}
		}

		if (_fireTime > 100)
		{
			while (!_tempBullet.empty())
			{
				_tempBullet.back()->setIsMove(true);
				_vBullet.push_back(_tempBullet.back());
				_tempBullet.pop_back();
			}

			_isFire = true;
			return true;
		}
	}
	
	return false;
}

void boss::setStar(float startX, float startY, float angle, float dist, BOSSBULLETSIZE size, int color)
{
	POINT p1;
	POINT p2;
	POINT p3;
	POINT p4;
	POINT p5;

	float _division = dist / 10;

	p1.x = startX + cosf(DEGREE(90) + angle) * dist;
	p1.y = startY - sinf(DEGREE(90) + angle) * dist;
	p2.x = p1.x + cosf(DEGREE(216) + angle) * dist;
	p2.y = p1.y - sinf(DEGREE(216) + angle) * dist;
	p3.x = p2.x + cosf(DEGREE(288) + angle) * dist;
	p3.y = p2.y - sinf(DEGREE(288) + angle) * dist;
	p4.x = p3.x + cosf(DEGREE(0) + angle) * dist;
	p4.y = p3.y - sinf(DEGREE(0) + angle) * dist;
	p5.x = p4.x + cosf(DEGREE(72) + angle) * dist;
	p5.y = p4.y - sinf(DEGREE(72) + angle) * dist;
	
	float fromp1 = GetAngle(p1.x, p1.y, p3.x, p3.y);
	float fromp2 = GetAngle(p2.x, p2.y, p4.x, p4.y);
	float fromp3 = GetAngle(p3.x, p3.y, p5.x, p5.y);
	float fromp4 = GetAngle(p4.x, p4.y, p1.x, p1.y);
	float fromp5 = GetAngle(p5.x, p5.y, p2.x, p2.y);

	float disp1 = GetDistance(p1.x, p1.y, p3.x, p3.y);
	float disp2 = GetDistance(p2.x, p2.y, p4.x, p4.y);
	float disp3 = GetDistance(p3.x, p3.y, p5.x, p5.y);
	float disp4 = GetDistance(p4.x, p4.y, p1.x, p1.y);
	float disp5 = GetDistance(p5.x, p5.y, p2.x, p2.y);

	

	for (float i = 1; i <= _division; i++)
	{
		makeBullet(p1.x + cosf(fromp1) * (disp1 / _division * i), p1.y - sinf(fromp1) * (disp1 / _division * i), fromp1, 0, size, PATERN7, color);
		makeBullet(p2.x + cosf(fromp2) * (disp2 / _division * i), p2.y - sinf(fromp2) * (disp2 / _division * i), fromp2, 0, size, PATERN7, color);
		makeBullet(p3.x + cosf(fromp3) * (disp3 / _division * i), p3.y - sinf(fromp3) * (disp3 / _division * i), fromp3, 0, size, PATERN7, color);
		makeBullet(p4.x + cosf(fromp4) * (disp4 / _division * i), p4.y - sinf(fromp4) * (disp4 / _division * i), fromp4, 0, size, PATERN7, color);
		makeBullet(p5.x + cosf(fromp5) * (disp5 / _division * i), p5.y - sinf(fromp5) * (disp5 / _division * i), fromp5, 0, size, PATERN7, color);
	}
}

void boss::updateBullet()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i]->update(0);
	}
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i]->getIsActivate() == false)
		{
			removeBullet(i);
		}
	}
	for (int i = 0; i < _tempBullet.size(); i++)
	{
		_tempBullet[i]->update(0);
	}
}

void boss::renderBullet()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i]->render();
	}
	for (int i = 0; i < _tempBullet.size(); i++)
	{
		_tempBullet[i]->render();
	}
}

void boss::setMagicCircle()
{
}

void boss::magicCircleMove()
{
}

void boss::magicCircleFire()
{
}
