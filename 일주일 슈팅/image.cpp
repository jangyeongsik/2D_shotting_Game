#include "stdafx.h"
#include "image.h"

HRESULT image::init(int width, int height)
{
	if (_image) release();

	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = CreateCompatibleBitmap(hdc, width, height);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool trans, COLORREF color, int frameX, int frameY)
{

	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;
	_image->isTrans = trans;
	_image->color = color;

	if (frameX > 0 || frameY > 0)
	{
		_image->frameX = 0;
		_image->frameY = 0;
		_image->maxFrameX = frameX - 1;
		_image->maxFrameY = frameY - 1;
		_image->frameWidth = width / frameX;
		_image->frameHeight = height / frameY;
		_image->isFrame = true;
	}

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::blendImageInit()
{
	HDC hdc = GetDC(_hWnd);

	_blendImage = new tagImageInfo;
	_blendImage->hdc = CreateCompatibleDC(hdc);
	_blendImage->hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hdc, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	_blendFunction.AlphaFormat = 0;
	_blendFunction.BlendFlags = 0;
	_blendFunction.BlendOp = AC_SRC_OVER;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::tempImageInit()
{
	HDC hdc = GetDC(_hWnd);

	_tempImage = new tagImageInfo;
	_tempImage->hdc = CreateCompatibleDC(hdc);
	_tempImage->hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_tempImage->hOBit = (HBITMAP)SelectObject(_tempImage->hdc, _tempImage->hBit);
	_tempImage->width = WINSIZEX;
	_tempImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_image)
	{
		SelectObject(_image->hdc, _image->hOBit);
		DeleteObject(_image->hBit);
		DeleteDC(_image->hdc);
		SAFEDELETE(_image);
	}
	if (_tempImage)
	{
		SelectObject(_tempImage->hdc, _tempImage->hBit);
		DeleteObject(_tempImage->hBit);
		SAFEDELETE(_tempImage);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void image::render(HDC hdc, int deseX, int destY, int sizeX, int sizeY)
{

	
	GdiTransparentBlt(
		hdc,
		deseX,
		destY,
		sizeX,
		sizeY,
		_image->hdc,
		0, 0,
		_image->width,
		_image->height,
		_image->color
	);
	
	
}

void image::renderCenter(HDC hdc, int deseX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourWidth,
			_image->hdc,
			sourX,
			sourY,
			sourWidth,
			sourHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			SRCCOPY
		);
	}
}

void image::frameRenderCenter(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - _image->frameWidth/2,
			destY - _image->frameHeight/2,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX - _image->frameWidth/2,
			destY - _image->frameHeight/2,
			_image->frameWidth,
			_image->frameHeight,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			SRCCOPY
		);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//오프셋(offset)은 일반적으로 동일 오브젝트 안에서 오브젝트 처음부터 주어진 요소나 특정 지점까지의 변위차
		//offset은 어떤 특정한 값에서 약간 차이가 나는 값 또는 그 차이 자체를 의미(차이에 따른 보정값)

		//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _image->width + (offsetX % _image->width);
	if (offsetY < 0) offsetY = _image->height + (offsetY % _image->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _image->height;
		rcSour.bottom = _image->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _image->width;
			rcSour.right = _image->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}


// size 부분엔 목표로하는 좌표를 입력
void image::strechRender(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{

	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			sizeX,
			sizeY,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempImage->hdc,
			0, 0,
			sizeX, sizeY,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX, destY,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);

	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_image->hdc,
			0,
			0,
			_image->width,
			_image->height,
			SRCCOPY
		);
	}

}


//size는 목표로하는 좌표 입력
void image::strechFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY)
{

	if (!_tempImage) tempImageInit();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_image->isTrans)
	{
		BitBlt(_tempImage->hdc, 0, 0,
			_image->width,
			_image->height,
			hdc,
			0,
			0,
			SRCCOPY);

		StretchBlt(
			_tempImage->hdc, 0, 0,
			sizeX, sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_tempImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->color
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_image->hdc,
			_image->frameWidth * frameX,
			_image->frameHeight * frameY,
			_image->frameWidth,
			_image->frameHeight,
			SRCCOPY
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height, _image->hdc,
			0, 0, _image->width, _image->height, _image->color);

		GdiAlphaBlend(
			hdc, destX, destY,
			_image->width, _image->height, _blendImage->hdc, 0, 0, _image->width, _image->height, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _image->width, _image->height, _image->hdc, 0, 0, _image->width, _image->height, _blendFunction);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, int frameX, int frameY)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->frameWidth, _image->frameHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->frameWidth, _image->frameHeight, _image->hdc,
			_image->frameWidth * frameX, _image->frameHeight * frameY, _image->frameWidth, _image->frameHeight, _image->color);

		GdiAlphaBlend(
			hdc, destX, destY,
			_image->frameWidth, _image->frameHeight, _blendImage->hdc, 0, 0, _image->frameWidth, _image->frameHeight, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _image->frameWidth, _image->frameHeight, _image->hdc, _image->frameWidth * frameX, _image->frameHeight * frameY, _image->frameWidth, _image->frameHeight, _blendFunction);
	}
}

void image::ASRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, BYTE alpha)
{
	if (!_tempImage) tempImageInit();
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{

	}
	else
	{
		BitBlt(
			_blendImage->hdc,
			0, 0,
			_image->width,
			_image->height,
			hdc,
			destX,
			destY,
			SRCCOPY);

		StretchBlt(
			_blendImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			SRCCOPY);

		GdiAlphaBlend
		(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_blendImage->hdc,
			0, 0,
			sizeX,
			sizeY,
			_blendFunction);
	}
}

void image::ASFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY, BYTE alpha)
{
	if (!_tempImage) tempImageInit();
	if (!_blendImage) blendImageInit();

	if (_image->isTrans)
	{

	}
	else
	{

	}
}

void image::minimapRender(HDC hdc, int deseX, int destY, float size)
{
	if (!_tempImage) tempImageInit();

	BitBlt(
		_tempImage->hdc,
		0, 0,
		_image->width,
		_image->height,
		hdc,
		0, 0, SRCCOPY);

	BitBlt(
		hdc,
		deseX,
		destY,
		_image->width * size,
		_image->height * size,
		_tempImage->hdc,
		0, 0, SRCCOPY);

}

