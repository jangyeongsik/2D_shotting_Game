#pragma once
#include "gameNode.h"
#include "discus.h"
#include "gameState.h"
#include "effect.h"
#include "effect_break.h"
#include "effect_score.h"

struct tagAim
{
	RECT rc;
	float x;
	float y;
	float toLeft;
	float toRight;
};

class shoot : public gameNode
{
private:

	vector<discus*> _vDiscus;
	vector<discus*>::iterator _viDiscus;

	vector<effect*> _vEffect;
	

	image* _pShootter;
	
	GAMESTATE _gameState;

	tagAim _leftAim;
	tagAim _rightAim;

	int _second;
	int _minute;
	int _coolTime;

	int _disCount;
	int _roundCount;

	int _firstScore;
	int _secondScore;
	int _thirdScore;
	int _currentScore;
public:
	shoot() {}
	~shoot() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void makeDiscus();
	void minDistance();

	void readyInit();
	void updateReady();
	void updateStart();
	void updateEnd();
	
	void makeBreakEffect(float x, float y);
	void makeScoreEffect(float x, float y, int score);
	void effectUpdate();

	float getLeftX() { return _leftAim.x; }
	float getRightX() { return _rightAim.x; }
};

