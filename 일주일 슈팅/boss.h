#pragma once
#include "gameNode.h"
#include "bullet_boss.h"

class player;
class mainGame;
class resultScene;

enum BOSSSTATE
{
	BOSS_LEFT,
	BOSS_RIGHT,
	BOSS_IDLE,
	BOSS_SKILL,
	BOSS_INIT,
	BOSS_DEAD
};

enum BOSSPHASE
{
	BOSS_PHASE1,
	BOSS_PHASE2
};

struct magicCircle
{
	image* ig;
	bool isActivate;
	float x, y;
	float angle;
	int fireTime;
};

class boss : public gameNode
{
private:
	mainGame* _mg;
	BOSSPHASE _bossPhase;
	player* _player;
	image* _bossImage;
	POINT _movePoint;
	int _moveTime;

	BOSSSTATE _bossState;
	float _x, _y;
	float _angle;
	RECT _bossRC;

	float _frameTime;
	int _frameX, _frameY;
	
	bool _isFire;
	int _fireCount;
	int _fireTime;
	int _patern;
	int _bulletColor;
	int _bulletColor2;
	int _offsetY;

	int _bossHp;

	queue<bullet_boss*> _qBullet;
	vector<bullet_boss*> _vBullet;
	vector<bullet_boss*> _tempBullet;

public:
	boss() {}
	~boss() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();
	void move();
	void setBossPhase();

	void makeBullet(float x, float y, float angle, float speed, BOSSBULLETSIZE size, BOSSBULLETPATERN patern, int color, bool isUP = false , float dist = 0);
	void removeBullet(int arr);
	void removeTempBullet(int arr);

	bool setPatern1();
	bool setPatern2();
	bool setPatern3();
	bool setPatern4();
	bool setPatern5();
	bool setPatern6();
	bool setPatern7();

	void setStar(float x, float y, float angle , float dist, BOSSBULLETSIZE size,int color);

	void updateBullet();
	void renderBullet();

	void setMagicCircle();
	void magicCircleMove();
	void magicCircleFire();

	float getX() { return _x;}
	float getY() { return _y; }
	RECT getRect() { return _bossRC; }
	vector<bullet_boss*> getBullet() { return _vBullet; }
	vector<bullet_boss*> getTempBullet() { return _tempBullet; }

	int getBossHp() { return _bossHp; }
	void setBossHP(int hp) { _bossHp -= hp; }

	void setPlayerAD(player* pl) { _player = pl; }
	void setMainGameAD(mainGame* mg) { _mg = mg; }
};

