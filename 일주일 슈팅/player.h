#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "bullet_player.h"

class enemyManager;
class boss;
class mainGame;

enum PLAYERSTATE
{
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_IDLE,
	PLAYER_DIE
};

enum PLAYERBULLETPOWER
{
	POWER1,
	POWER2,
	POWER3,
	POWER4,

};

class player : public gameNode
{
private:
	enemyManager* _em;
	boss* _boss;
	mainGame* _mg;
	queue<bullet_player*> _qBullet;
	vector<bullet_player*> _vBullet;					//이거 돌리려고하는데요
	vector<bullet_player*>::iterator _vIBullet;
	PLAYERSTATE _pState;
	PLAYERBULLETPOWER _bPower;
	RECT _playerRc;
	float _x;
	float _y;
	float _speed;
	float _fireTime;
	float _minDistance;
	float _minAngle;

	image* _playerImage;


	float _frameTime;
	int _frameX;

	int _playerLife;
	int _playerPower;


	POINT _bust1;
	POINT _bust2;
	int _alpha;
	int _alphaTime;
	bool _isAlpha;
	int _charNum;
public:
	player() {}
	~player() {}


	HRESULT init();
	void release();
	void update();
	void render();

	void collisionEnemy();
	void collisionBoss();
	void collisionItem();
	void animation();
	void makeBullet();
	void keyInput();
	void removeBullet(int arr);

	void pushBullet(bullet_player* _bullet);
	bullet_player* popBullet(float x, float y, float angle, bool _isHom = false);

	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRect() { return _playerRc; }
	int getPlayerLife() { return _playerLife; }
	int getPlayerPower() {return _playerPower;	}

	void setCharNum(int num) { _charNum = num; }
	void setEnemyManagerAD(enemyManager* em) { _em = em; }
	void setBossAD(boss* bos) { _boss = bos; }
	void setMainGameAD(mainGame* mg) { _mg = mg; }
};

