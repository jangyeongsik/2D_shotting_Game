#pragma once
#include "singletonBase.h"
#include "image.h"
class imageManager : public singletonBase<imageManager>
{
private:
	map<string, image*> _mImage;
	typedef map<string, image*>::iterator mImageIter;

public:
	imageManager() {}
	~imageManager() {}

	image* addImage(string key, int width, int height);
	image* addImage(string key, const char* fileName, int width, int height, bool trans, COLORREF color, int frameX = 0, int frameY = 0);
	image* findImage(string key);
	bool deleteImage(string key);
	void clearImage();

};

