#pragma once
class image
{
public:
	struct tagImageInfo
	{
		HDC hdc;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		int frameX;
		int frameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		bool isTrans;
		bool isFrame;
		COLORREF color;

		tagImageInfo()
		{
			hdc = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			width = 0;
			height = 0;
			frameX = 0;
			frameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			isTrans = false;
			isFrame = false;
			color = RGB(0, 0, 0);
		}
	};

private:
	tagImageInfo* _image;
	tagImageInfo* _tempImage;
	tagImageInfo* _blendImage;

	BLENDFUNCTION _blendFunction;

public:
	image()
		:_image(nullptr), _tempImage(nullptr) {}
	~image() {}

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, bool trans, COLORREF color, int frameX = 0, int frameY = 0);
	HRESULT blendImageInit();
	HRESULT tempImageInit();

	void release();

	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int deseX, int destY,int sizeX, int sizeY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void renderCenter(HDC hdc, int deseX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int frameX = 0, int frameY = 0);
	void frameRenderCenter(HDC hdc, int destX, int destY, int frameX = 0, int frameY = 0);
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void strechRender(HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void strechFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, int frameX, int frameY);
	void ASRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, BYTE alpha);
	void ASFrameRender(HDC hdc, int destX, int destY, int sizeX, int sizeY, int frameX, int frameY, BYTE alpha);

	void minimapRender(HDC hdc, int deseX, int destY, float size);

	int getWidth() { return _image->width; }
	int getHeight() { return _image->height; }
	int getFrameX() { return _image->frameX; }
	int getFrameY() { return _image->frameY; }
	int getMaxFrameX() { return _image->maxFrameX; }
	int getMaxFrameY() { return _image->maxFrameY; }
	int getFrameWidth() { return _image->frameWidth; }
	int getFrameHeight() { return _image->frameHeight; }

	HDC getHDC() { return _image->hdc; }
};

