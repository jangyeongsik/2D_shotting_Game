#include "stdafx.h"
#include "gameNode.h"

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	SetTimer(_hWnd, 1, 10, NULL);
	srand(GetTickCount());
	TIMEMANAGER->init();
	INPUT->init();
	IMAGEMANAGER->addImage("¹é¹öÆÛ", WINSIZEX, WINSIZEY);
	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	INPUT->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
	TIMEMANAGER->update();
}

void gameNode::render()
{
}

LRESULT gameNode::wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		this->render();
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}
