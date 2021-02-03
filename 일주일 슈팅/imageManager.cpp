#include "stdafx.h"
#include "imageManager.h"

image * imageManager::addImage(string key, int width, int height)
{
	image* img = findImage(key);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImage.insert(make_pair(key, img));

	return img;
}

image * imageManager::addImage(string key, const char * fileName, int width, int height, bool trans, COLORREF color, int frameX, int frameY)
{
	image* img = findImage(key);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(fileName, width, height, trans, color,frameX,frameY)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImage.insert(make_pair(key, img));

	return img;
}

image * imageManager::findImage(string key)
{
	mImageIter _key = _mImage.find(key);

	if (_key != _mImage.end())
	{
		return _key->second;
	}

	return nullptr;
}

bool imageManager::deleteImage(string key)
{
	mImageIter _key = _mImage.find(key);

	//검색한 키를 찾았다면 이미지를 삭제하자
	if (_key != _mImage.end())
	{
		//이미지 해제
		_key->second->release();
		//메모리 해제
		SAFE_DELETE(_key->second);
		//맵의 반복자 해제
		_mImage.erase(_key);

		return true;
	}

	return false;
}

void imageManager::clearImage()
{
	_mImage.clear();
}
