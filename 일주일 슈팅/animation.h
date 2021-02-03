#pragma once
class animation
{
private:

	float _renderSpeed;
	float _time;

	int _maxFrameX;
	int _maxFrameY;
	int _frameWidth;
	int _FrameHeight;
	int _frameX;
	int _frameY;

	int _destX;
	int _destY;

	bool _isRender;
	bool _isLoop;
	bool _isReverse;

public:
	animation() {}
	~animation() {}

	HRESULT init(image* ig, bool isLoop, bool isReverse);
	void frameUpdate();
	void render(HDC hdc,image* ig);
	void render(HDC hdc,image* ig,int destX, int destY);
	void setRenderSpeed(float speed);
	void setRenderPoint(int destX, int destY) { _destX = destX; _destY = destY; }

	void renderStart() { _isRender = true; }
	void stopRender() { _isRender = false; }

	int getX() { return _frameX; }
	int getMax() { return _maxFrameX; }
	bool getIsRender() { return _isRender; }
	int getWidth() { return _FrameHeight; }

};

