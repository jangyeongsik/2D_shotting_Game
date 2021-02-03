#pragma once
#include "gameNode.h"
#include "animation.h"
#include "mainScene.h"
#include "playScene.h"
#include "selectScene.h"
#include "resultScene.h"
#include "item.h"

enum SCENESTATE
{
	MAINSCENE,
	SELECTSCENE,
	PLAYSCENE,
	RESULTSCENE
};


class mainGame : public gameNode
{
private:

	SCENESTATE _scene;

	mainScene _mainS;
	selectScene _selectS;
	playScene _playS;
	resultScene _result;
	int _currentChar;

public:
	mainGame() {}
	~mainGame() {}

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void imageInit();
	
	void setScene(SCENESTATE scene) { _scene = scene; }
	void setScene(SCENESTATE scene, int charNum) { _scene = scene; _currentChar = charNum; }
	int getCharNum() { return _currentChar; }
};

