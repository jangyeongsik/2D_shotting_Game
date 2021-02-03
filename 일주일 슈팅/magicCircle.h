#pragma once
class magicCircle
{
private:
	static magicCircle* _inst;
	magicCircle() {}
	~magicCircle() {}
public:

	static magicCircle* getInstance()
	{
		if (_inst == nullptr) _inst = new magicCircle;
		return _inst;
	}
	void release()
	{
		if (_inst)
		{
			delete _inst;
			_inst = nullptr;
		}
	}

private:
	float _x, _y;
	float _pivotX, _pivotY;
	


};

class magicCircleManager
{
private:
	static magicCircleManager* _inst;

	magicCircleManager() {}
	~magicCircleManager() {}

public:
};
