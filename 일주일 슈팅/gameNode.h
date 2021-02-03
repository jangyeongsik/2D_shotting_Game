#pragma once
#include "image.h"

class gameNode
{
private:
	
	HDC _hdc;
public:
	gameNode() {}
	virtual ~gameNode() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	LRESULT CALLBACK wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	image* getBackBuffer() { return IMAGEMANAGER->findImage("백버퍼"); }
	HDC getMemDC() { return IMAGEMANAGER->findImage("백버퍼")->getHDC(); }
	HDC getHDC() { return _hdc; }
};

