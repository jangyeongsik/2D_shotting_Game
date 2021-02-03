#include "stdafx.h"
#include "shoot.h"

HRESULT shoot::init()
{
	_second = 600;
	_minute = 15;

	_firstScore = 0;
	_secondScore = 0;
	_thirdScore = 0;
	_currentScore = 0;

	_leftAim.x = WINSIZEX / 2 - 100;
	_leftAim.y = WINSIZEY / 2 + 100;	
	_leftAim.rc = RectMakeCenter(_leftAim.x, _leftAim.y, 56, 56);

	_rightAim.x = WINSIZEX / 2 + 100;
	_rightAim.y = WINSIZEY / 2 + 100;
	_rightAim.rc = RectMakeCenter(_rightAim.x, _rightAim.y, 56, 56);

	_pShootter = IMAGEMANAGER->findImage("shootCenter");

	_gameState = GAMEREADY;

	return S_OK;
}

void shoot::release()
{
}

void shoot::update()
{
	switch (_gameState)
	{
	case GAMEREADY:
		updateReady();
		break;
	case GAME1ST:
		updateStart();
		break;
	case GAME2ND:
		updateStart();
		break;
	case GAME3RD:
		updateStart();
		break;
	case GAMEEND:
		break;
	default:
		break;
	}

}

void shoot::render()
{
	IMAGEMANAGER->findImage("shootBack")->render(getMemDC(), 0, 0);// 배경

	char temp[128];
	wsprintf(temp, "whiteNum%d", (_minute / 10)%10);
	IMAGEMANAGER->findImage(temp)->render(getMemDC(), 645, 640); // 분 십의자리
	wsprintf(temp, "whiteNum%d", _minute % 10);
	IMAGEMANAGER->findImage(temp)->render(getMemDC(), 680, 640); // 분 일의자리
	wsprintf(temp, "whiteNum%d", (_second/100) % 10);
	IMAGEMANAGER->findImage(temp)->render(getMemDC(), 735, 640); // 초 십의자리
	wsprintf(temp, "whiteNum%d", (_second/10) % 10);
	IMAGEMANAGER->findImage(temp)->render(getMemDC(), 770, 640); // 초 일의자리

	for (int i = 1, di = 0; i <= _firstScore; i *= 10)
	{
		wsprintf(temp, "whiteNum%d", (_firstScore / i) % 10);
		IMAGEMANAGER->findImage(temp)->render(getMemDC(), 965 - (di * 33), 768);// 1트 점수위치
		di++;
	}
	for (int i = 1, di = 0; i <= _secondScore; i *= 10)
	{
		wsprintf(temp, "whiteNum%d", (_secondScore / i) % 10);
		IMAGEMANAGER->findImage(temp)->render(getMemDC(), 965 - (di * 33), 800);// 2트 점수위치
		di++;
	}
	for (int i = 1, di = 0; i <= _thirdScore; i *= 10)
	{
		wsprintf(temp, "whiteNum%d", (_thirdScore / i) % 10);
		IMAGEMANAGER->findImage(temp)->render(getMemDC(), 965 - (di * 33), 836); // 3트 점수위치
		di++;
	}
	for (int i = 1, di = 0; i <= _currentScore; i *= 10)
	{
		wsprintf(temp, "whiteNum%d", (_currentScore / i) % 10);
		IMAGEMANAGER->findImage(temp)->render(getMemDC(), 350 - (di * 33), 735); // 3트 점수위치
		di++;
	}

	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->render();
	}

	//IMAGEMANAGER->findImage("whiteNum0")->render(getMemDC(), 230, 735); // 현재 스코어

	IMAGEMANAGER->findImage("aim")->render(getMemDC(), _leftAim.rc.left, _leftAim.rc.top);
	IMAGEMANAGER->findImage("aim")->render(getMemDC(), _rightAim.rc.left, _rightAim.rc.top);

	for (int i = 0; i < _vDiscus.size(); i++)
	{
		_vDiscus[i]->render();
	}

	_pShootter->render(getMemDC(), 400, 550);

}

void shoot::makeDiscus()
{
	discus* _dis = new discus;
	_dis->init(962,566);
	_dis->setShootAdress(this);
	_vDiscus.push_back(_dis);
}

void shoot::minDistance()
{
	if (_leftAim.y < WINSIZEY / 2 + 100) _leftAim.y+=3;
	if (_rightAim.y < WINSIZEY / 2 + 100) _rightAim.y+=3;

	int li = 0;
	int ri = 0;

	float ml = 0.f;
	float mr = 0.f;
	
	for (int i = 0; i < _vDiscus.size(); i++)
	{
		if (_vDiscus[i]->getIsRight() == true)
		{
			if (_vDiscus[i]->getX() > _leftAim.x - 200 && _vDiscus[i]->getX() < _leftAim.x + 28)
			{
				if (ml == 0 || _leftAim.x - _vDiscus[i]->getX() < ml)
				{
					_leftAim.y = _vDiscus[i]->getY();
					ml = _leftAim.x - _vDiscus[i]->getX();
				}
			
				
			}
			else if (_vDiscus[i]->getX() > _leftAim.x + 28 && _vDiscus[i]->getX() < _rightAim.x + 28)
			{
				if (mr == 0 || _rightAim.x - _vDiscus[i]->getX() < mr)
				{
					_rightAim.y = _vDiscus[i]->getY();
					mr = _rightAim.x - _vDiscus[i]->getX();
				}
			}
		}
		else
		{
			if (_vDiscus[i]->getX() < _rightAim.x + 200 && _vDiscus[i]->getX() > _rightAim.x - 28)
			{
				if (mr == 0 || _vDiscus[i]->getX() - _rightAim.x < mr)
				{
					_rightAim.y = _vDiscus[i]->getY();
					mr = _vDiscus[i]->getX() - _rightAim.x;
				}
				

			}
			else if (_vDiscus[i]->getX() < _rightAim.x - 28 && _vDiscus[i]->getX() > _leftAim.x - 28)
			{
				if (ml == 0 || _vDiscus[i]->getX() - _leftAim.x < ml)
				{
					_leftAim.y = _vDiscus[i]->getY();
					ml = _vDiscus[i]->getX() - _leftAim.x;
				}
			
			}
		}
	}



	_leftAim.rc = RectMakeCenter(_leftAim.x, _leftAim.y, 56, 56);
	_rightAim.rc = RectMakeCenter(_rightAim.x, _rightAim.y, 56, 56);
}

void shoot::readyInit()
{
	_second = 600;
	_minute = 15;
	_currentScore = 0;
	_disCount = 0;

	_leftAim.x = WINSIZEX / 2 - 100;
	_leftAim.y = WINSIZEY / 2 + 100;
	_leftAim.rc = RectMakeCenter(_leftAim.x, _leftAim.y, 56, 56);

	_rightAim.x = WINSIZEX / 2 + 100;
	_rightAim.y = WINSIZEY / 2 + 100;
	_rightAim.rc = RectMakeCenter(_rightAim.x, _rightAim.y, 56, 56);
	_gameState = GAMEREADY;

	_vDiscus.clear();
	_vEffect.clear();
	
}

void shoot::updateReady()
{
	if (INPUT->GetKeyDown(VK_SPACE))
	{
		switch (_roundCount)
		{
		case 0:
			_roundCount++;
			_gameState = GAME1ST;
			break;
		case 1:
			_roundCount++;
			_gameState = GAME2ND;
			break;
		case 2:
			_roundCount++;
			_gameState = GAME3RD;
			break;
		}
	}
}

void shoot::updateStart()
{
	_second--;

	if (_minute == 0 && _second < 0)
	{
		switch (_gameState)
		{
		case GAME1ST:
			_gameState = GAMEREADY;
			break;
		case GAME2ND:
			_gameState = GAMEREADY;
			break;
		case GAME3RD:
			_gameState = GAMEEND;
			break;
		}
	}

	if (_second % 100 == 0)
	{
		makeDiscus();
	}

	if (_second < 0)
	{
		_minute--;
		_second = 600;
	}

	for (int i = 0; i < _vDiscus.size(); i++)
	{
		_vDiscus[i]->update();

	}
	for (int i = 0; i < _vDiscus.size(); i++)
	{
		if (_vDiscus[i]->getX() < 0 ||
			_vDiscus[i]->getX() > WINSIZEX ||
			_vDiscus[i]->getY() > WINSIZEY)
		{
			_vDiscus.erase(_vDiscus.begin() + i);
			_disCount++;

			if (_disCount > 20)
			{
				readyInit();
			}
			break;
		}
	}

	if (INPUT->GetKeyDown('A'))
	{
		_pShootter = IMAGEMANAGER->findImage("shootLeft");

		RECT temp;
		for (int i = 0; i < _vDiscus.size(); i++)
		{
			if (IntersectRect(&temp, &_leftAim.rc, &_vDiscus[i]->getRect()))
			{
				_disCount++;
				switch (_gameState)
				{
				case GAME1ST:
					_firstScore += _vDiscus[i]->getScore();
					break;
				case GAME2ND:
					_secondScore += _vDiscus[i]->getScore();
					break;
				case GAME3RD:
					_thirdScore += _vDiscus[i]->getScore();
					break;
				}

				makeBreakEffect(_vDiscus[i]->getX(), _vDiscus[i]->getY());
				makeScoreEffect(_vDiscus[i]->getX(), _vDiscus[i]->getY(), _vDiscus[i]->getScore());

				_vDiscus.erase(_vDiscus.begin() + i);

				if (_disCount > 20)
				{
					readyInit();
				}
				break;
			}
		}
	}
	if (INPUT->GetKeyDown('D'))
	{
		_pShootter = IMAGEMANAGER->findImage("shootRight");

		RECT temp;
		for (int i = 0; i < _vDiscus.size(); i++)
		{
			if (IntersectRect(&temp, &_rightAim.rc, &_vDiscus[i]->getRect()))
			{
				_disCount++;

				switch (_gameState)
				{
				case GAME1ST:
					_firstScore += _vDiscus[i]->getScore();
					break;
				case GAME2ND:
					_secondScore += _vDiscus[i]->getScore();
					break;
				case GAME3RD:
					_thirdScore += _vDiscus[i]->getScore();
					break;
				}

				makeBreakEffect(_vDiscus[i]->getX(), _vDiscus[i]->getY());
				makeScoreEffect(_vDiscus[i]->getX(), _vDiscus[i]->getY(), _vDiscus[i]->getScore());

				_vDiscus.erase(_vDiscus.begin() + i);

				if (_disCount > 20)
				{
					readyInit();
				}
				break;
			}
		}
	}
	if (INPUT->GetKeyUp('A'))
	{
		_pShootter = IMAGEMANAGER->findImage("shootCenter");
	}
	if (INPUT->GetKeyUp('D'))
	{
		_pShootter = IMAGEMANAGER->findImage("shootCenter");
	}

	switch (_gameState)
	{
	case GAME1ST:
		_currentScore = _firstScore;
		break;
	case GAME2ND:
		_currentScore = _secondScore;
		break;
	case GAME3RD:
		_currentScore = _thirdScore;
		break;
	}

	effectUpdate();
	
	minDistance();
}

void shoot::updateEnd()
{

}

void shoot::makeBreakEffect(float x, float y)
{
	effect* _ef = new effect_break;
	_ef->init(x, y);
	_vEffect.push_back(_ef);
}

void shoot::makeScoreEffect(float x, float y, int score)
{
	effect* _ef = new effect_score;
	dynamic_cast<effect_score*>(_ef)->init(x, y, score);
	_vEffect.push_back(_ef);

}

void shoot::effectUpdate()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->update();
	}
	for (int i = 0; i < _vEffect.size(); i++)
	{
		if (_vEffect[i]->getDelete())
		{
			_vEffect.erase(_vEffect.begin() + i);
		}
	}
}
