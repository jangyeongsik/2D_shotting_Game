#pragma once
#include "enemy.h"
#include "enemy_red.h"
#include "enemy_blue.h"
#include "gameNode.h"
#include "bullet_enemy.h"

class enemyManager : public gameNode
{
private:

	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _vIEnemy;

	queue<bullet_enemy*> _qBullet;

	vector<bullet_enemy*> _vBullet;
	vector<bullet_enemy*>::iterator _vIBullet;


	float _redEnemySetPos;


	int _redEnemySetTime;
	int _blueEnemySetTime;
	int _blueSetCount;

	int _enemyKillCount;

public:
	enemyManager() {}
	~enemyManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setRecEnemy();
	void setBlueEnemy();
	void updateBullet();
	void pushBullet(float x, float y, float angle);
	void popBullet(bullet_enemy* eb);

	void removeEnemy(int arr);
	void removeBullet(int arr);

	vector<enemy*> getEnemyVector() { return _vEnemy; }
	vector<bullet_enemy*> getEnemyBullet() { return _vBullet; }
	int getKillCount() { return _enemyKillCount; }
};

